#ifndef __SMART_CONFIG_H__
#define __SMART_CONFIG_H__

#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "tcpip_adapter.h"
#include "esp_smartconfig.h"

#include "wifi.h"

static const int ESPTOUCH_DONE_BIT = BIT2;

void smartconfig_init(void);

#endif
