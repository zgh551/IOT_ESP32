#ifndef __FLASH_NVS__
#define __FLASH_NVS__

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"

void flash_nvs_init(void);

#endif