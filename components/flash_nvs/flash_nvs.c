#include "flash_nvs.h"

static const char *TAG = "flash_nvs";

void flash_nvs_init(void)
{
    // Initialize NVS
    ESP_LOGI(TAG, "NVS Flash Init");
    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}