#ifndef __WIFI_H__
#define __WIFI_H__

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "rom/ets_sys.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"

/* FreeRTOS event group to signal when we are connected*/
extern EventGroupHandle_t wifi_event_group;
/* The event group allows multiple bits for each event,
   but we only care about one event - are we connected
   to the AP with an IP? */
static const int START_BIT     = BIT0;
static const int CONNECTED_BIT = BIT1;

// void wifi_init(void);
void wifi_init_smartconfig(void);

#endif