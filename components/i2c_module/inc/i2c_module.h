#ifndef __I2C_MODULE_H__
#define __I2C_MODULE_H__

#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"

#define I2C_MASTER_SCL_IO  26               /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO  25               /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM     0                /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ 100000           /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0         /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0         /*!< I2C master doesn't need buffer */

#define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ                /*!< I2C master read */
#define ACK_CHECK_EN           0x1              /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS          0x0              /*!< I2C master will not check ack from slave */
#define ACK_VAL                0x0              /*!< I2C ack value */
#define NACK_VAL               0x1              /*!< I2C nack value */
#define LAST_NACK_VAL          0x2              /*!< I2C last_nack value */
/**
 * @brief i2c master initialization
 */
esp_err_t i2c_master_init();

/**
 * @brief test code to read esp-i2c-slave
 *        We need to fill the buffer of esp slave device, then master can read them out.
 *
 * _______________________________________________________________________________________
 * | start | slave_addr + rd_bit +ack | read n-1 bytes + ack | read 1 byte + nack | stop |
 * --------|--------------------------|----------------------|--------------------|------|
 *
 */
esp_err_t i2c_master_read_datas(i2c_port_t i2c_num, uint8_t slave_add,uint8_t reg_address,uint8_t *data_rd, size_t size);
esp_err_t i2c_master_read_data_only(i2c_port_t i2c_num, uint8_t slave_add,uint8_t *data_rd, size_t size);
/**
 * @brief i2c write operation, write the regist address with the data
 *
 * 1. send data
 * ___________________________________________________________________________________________________
 * | start | slave_addr + wr_bit + ack | write reg_address + ack | write data_len byte + ack  | stop |
 * --------|---------------------------|-------------------------|----------------------------|------|
 *
 * @param i2c_num I2C port number
 * @param sensor_add the address of the sensor
 * @param reg_address slave reg address
 * @param data data to send
 * @param data_len data length
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 *     - ESP_FAIL Sending command error, slave doesn't ACK the transfer.
 *     - ESP_ERR_INVALID_STATE I2C driver not installed or not in master mode.
 *     - ESP_ERR_TIMEOUT Operation timeout because the bus is busy.
 */
esp_err_t i2c_master_write_datas(i2c_port_t i2c_num, uint8_t slave_add, uint8_t reg_address, uint8_t *data, size_t data_len);

/**
 * @brief Test code to write esp-i2c-slave
 *        Master device write data to slave(both esp32),
 *        the data will be stored in slave buffer.
 *        We can read them out from slave buffer.
 *
 * ___________________________________________________________________
 * | start | slave_addr + wr_bit + ack | write n bytes + ack  | stop |
 * --------|---------------------------|----------------------|------|
 *
 */
esp_err_t i2c_master_write_reg(i2c_port_t i2c_num, uint8_t slave_add,uint8_t reg_address);
#endif
