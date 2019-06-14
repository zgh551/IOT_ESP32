#include "ccs811.h"

static const char *TAG = "CCS811";
CCS811_SensorPacket m_CCS811_SensorPacket;
QueueHandle_t CCS811_SensorQueue;

static void ccs811_init(i2c_port_t i2c_num)
{
    uint8_t i2c_buff[8];
    CCS811_SensorQueue = xQueueCreate(10,sizeof(CCS811_SensorPacket));

    vTaskDelay(100 / portTICK_RATE_MS);
    ESP_ERROR_CHECK(i2c_master_read_datas(i2c_num,CCS811_SENSOR_ADDR,HW_ID,i2c_buff,1)); 
    ESP_LOGI(TAG, "Hardware ID:0x%x",i2c_buff[0]);
    ESP_ERROR_CHECK(i2c_master_read_datas(i2c_num,CCS811_SENSOR_ADDR,HW_VERSION,i2c_buff,2));
    ESP_LOGI(TAG, "Hardware Version:0x%x",i2c_buff[0]);
    ESP_ERROR_CHECK(i2c_master_read_datas(i2c_num,CCS811_SENSOR_ADDR,FW_BOOT_VERSION,i2c_buff,2));
    ESP_LOGI(TAG, "Fireware Boot Version:0x%x",i2c_buff[0]);
    ESP_ERROR_CHECK(i2c_master_read_datas(i2c_num,CCS811_SENSOR_ADDR,FW_APP_VERSION,i2c_buff,2));
    ESP_LOGI(TAG, "Fireware App Version:0x%x",i2c_buff[0]);

    ESP_ERROR_CHECK(i2c_master_read_datas(i2c_num,CCS811_SENSOR_ADDR,STATUS,i2c_buff,1));
    ESP_LOGI(TAG, "Status:0x%x",i2c_buff[0]);
    if( i2c_buff[0] & 0x10)
    {

        ESP_LOGI(TAG, "Valid application firmware loaded");
        int ret = i2c_master_write_reg(i2c_num,CCS811_SENSOR_ADDR,APP_START);
        ESP_LOGI(TAG, "Write Status %d",ret);
        vTaskDelay(1000 / portTICK_RATE_MS);
        ret = i2c_master_read_datas(i2c_num,CCS811_SENSOR_ADDR,STATUS,i2c_buff,1);
        ESP_LOGI(TAG, "APP Status:0x%x %d",i2c_buff[0],ret);

        i2c_buff[0] = DRIVE_MODE_1SEC | INTERRUPT_DRIVEN;
        ret = i2c_master_write_datas(i2c_num,CCS811_SENSOR_ADDR,MEAS_MODE, i2c_buff, 1);
        ESP_LOGI(TAG, "Write Status %d",ret);
    }
    else
    {
        ESP_LOGI(TAG, "No application firmware loaded");
    }
}

/**
 * @brief the ccs811 task
*/
static void ccs811_task(void *arg)
{
    uint8_t i2c_buff[8];
    ccs811_init(I2C_MASTER_NUM);
    while(1)
    {
        i2c_master_read_datas(I2C_MASTER_NUM,CCS811_SENSOR_ADDR,ALG_RESULT_DATA,i2c_buff,8);
        if(i2c_buff[4] & 0x08)
        {
            m_CCS811_SensorPacket.TVOC = (uint16_t)((i2c_buff[2] << 8) | i2c_buff[3])
            m_CCS811_SensorPacket.CO2  = (uint16_t)((i2c_buff[0] << 8) | i2c_buff[1]);
            if( xQueueSend(CCS811_SensorQueue,(void *) &m_CCS811_SensorPacket,(TickType_t)100) != pdPASS )
            {
                /* 发送失败，即使等待了10个时钟节拍 */
            }
            else
            {
                /* 发送成功 */                   
            }
            ESP_LOGI(TAG, "CO2: %d ;TVOC: %d",m_CCS811_SensorPacket.CO2 ,m_CCS811_SensorPacket.TVOC );
        }
        // ESP_LOGI(TAG, "Receive Data 0x%x 0x%x 0x%x 0x%x",i2c_buff[0],i2c_buff[1],i2c_buff[2],i2c_buff[3]);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

/**
 * @brief create the cs811 task
*/
void ccs811_task_init()
{
    xTaskCreate(ccs811_task, "ccs811_task", 4096, NULL, 10, NULL);
}
