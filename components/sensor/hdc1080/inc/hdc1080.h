#ifndef __HDC1080_H__
#define __HDC1080_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"
#include "esp_system.h"
#include "esp_err.h"

#include "driver/i2c.h"
#include "i2c_module.h"

#define HDC1080_SENSOR_ADDR                 0x40             /*!< slave address for HDC1080 sensor */
/**
 * Define the hdc1080 register address:
 */
#define TEMPERATURE     0x00
#define HUMIDITY        0x01
#define CONFIGURATION   0x02

#define SERIAL_ID_F     0xFB
#define SERIAL_ID_M     0xFC
#define SERIAL_ID_L     0xFD
#define MANUFACTURER_ID 0xFE
#define DEVICE_ID       0xFF

void hdc1080_task_init();

#endif