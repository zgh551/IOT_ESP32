#include "hdc1080.h"

static const char *TAG = "HDC1080";

static void hdc1080_init(i2c_port_t i2c_num)
{
    uint8_t i2c_buff[8];
    // vTaskDelay(100 / portTICK_RATE_MS);
    int ret = i2c_master_read_datas(i2c_num,HDC1080_SENSOR_ADDR,DEVICE_ID,i2c_buff,2); 
    ESP_LOGI(TAG, "Device ID:0x%x 0x%x %d",i2c_buff[0],i2c_buff[1],ret);

    ret = i2c_master_read_datas(i2c_num,HDC1080_SENSOR_ADDR,MANUFACTURER_ID,i2c_buff,2); 
    ESP_LOGI(TAG, "Manufacture ID:0x%x 0x%x %d",i2c_buff[0],i2c_buff[1],ret);

    ret = i2c_master_read_datas(i2c_num,HDC1080_SENSOR_ADDR,SERIAL_ID_F,i2c_buff,2); 
    ESP_LOGI(TAG, "SERIAL_ID_F:0x%x 0x%x %d",i2c_buff[0],i2c_buff[1],ret);

    ret = i2c_master_read_datas(i2c_num,HDC1080_SENSOR_ADDR,SERIAL_ID_M,i2c_buff,2); 
    ESP_LOGI(TAG, "SERIAL_ID_M:0x%x 0x%x %d",i2c_buff[0],i2c_buff[1],ret);

    ret = i2c_master_read_datas(i2c_num,HDC1080_SENSOR_ADDR,SERIAL_ID_L,i2c_buff,2); 
    ESP_LOGI(TAG, "SERIAL_ID_L:0x%x 0x%x %d",i2c_buff[0],i2c_buff[1],ret);

    ret = i2c_master_read_datas(i2c_num,HDC1080_SENSOR_ADDR,CONFIGURATION,i2c_buff,2); 
    ESP_LOGI(TAG, "CONFIGURATION:0x%x 0x%x %d",i2c_buff[0],i2c_buff[1],ret);

    i2c_buff[0]= 0x10;
    i2c_buff[1]= 0x00;
    ret = i2c_master_write_datas(i2c_num,HDC1080_SENSOR_ADDR,CONFIGURATION,i2c_buff,2);
    ESP_LOGI(TAG, "Write status:%d",ret);
}


void hdc1080_task_init()
{
    uint8_t i2c_buff[8];
    hdc1080_init(I2C_MASTER_NUM);
    while(1)
    {
        int ret = i2c_master_write_reg(I2C_MASTER_NUM,HDC1080_SENSOR_ADDR,TEMPERATURE);
        // ESP_LOGI(TAG, "Write status:%d",ret);
        vTaskDelay(1000 / portTICK_RATE_MS);

        ret = i2c_master_read_data_only(I2C_MASTER_NUM,HDC1080_SENSOR_ADDR,i2c_buff,4); 
        ESP_LOGI(TAG, "TEMPERATURE:%f; HUMIDITY:%f",(uint16_t)((i2c_buff[0] << 8) | i2c_buff[1])*165.0/65535 - 40,(uint16_t)((i2c_buff[2] << 8) | i2c_buff[3])*100.0/65535);

        // ret = i2c_master_read_datas(I2C_MASTER_NUM,HDC1080_SENSOR_ADDR,HUMIDITY,i2c_buff,2); 
        // ESP_LOGI(TAG, "HUMIDITY:%f %d",(uint16_t)((i2c_buff[2] << 8) | i2c_buff[3])*100.0/65535,ret);

        
    }
}