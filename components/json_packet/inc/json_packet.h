#ifndef __JSON_PACKET_H__
#define __JSON_PACKET_H__

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_system.h"
#include "esp_log.h"

#include "cJSON.h"


void SensorPushPacket(char * s);
void AckPushPacket(uint32_t id,uint32_t led_value,char * s);
int8_t SwitchPacketParse(char * s,uint32_t *id,uint32_t *led_value);

#endif
