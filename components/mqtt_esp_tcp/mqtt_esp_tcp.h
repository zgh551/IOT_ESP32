#ifndef __MQTT_ESP_TCP_H__
#define __MQTT_ESP_TCP_H__

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
// #include "tcpip_adapter.h"
// #include "protocol_examples_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"

#include "wifi.h"
#include "smart_config.h"
#include "cJSON.h"
// #include "led.h"
#include "driver/gpio.h"
#include "json_packet.h"

void mqtt_esp_tcp_init(void);
#endif
