#include "mqtt_esp_tcp.h"

static const char *TAG = "MQTT_ESP_TCP";
char MqttPubTopic[24] ={0};
char MqttSubTopic[24] ={0};

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");

            // msg_id = esp_mqtt_client_publish(client, "/topic/qos1", "data_3", 0, 1, 0);
            // ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);

            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            // msg_id = esp_mqtt_client_publish(client, "/topic/qos0", "data", 0, 0, 0);
            // ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            printf("DATA=%.*s\r\n", event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            break;
        default:
            ESP_LOGI(TAG, "Other event id:%d", event->event_id);
            break;
    }
    return ESP_OK;
}




void mqtt_sensor_task(void * parm)
{
    int msg_id;

    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    //获取mac地址（station模式）
    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA);
    sprintf(MqttPubTopic,"1/%02x%02x%02x%02x%02x%02x/set",mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    sprintf(MqttSubTopic,"1/%02x%02x%02x%02x%02x%02x/get",mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    // 配置 mqtt 参数
    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = "mqtt://120.77.245.155:62000",
        .event_handle = mqtt_event_handler,
    };

    // 等待网络连接
    ESP_LOGI(TAG, "wait wifi connect...");
    xEventGroupWaitBits(wifi_event_group, ESPTOUCH_DONE_BIT, false, true, portMAX_DELAY);

    // 配置mqtt参数，并启动MQTT服务
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);

    msg_id = esp_mqtt_client_subscribe(client,MqttSubTopic, 1);
    ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
    
    while(1)
    {

    }
}

void mqtt_esp_tcp_init(void)
{
    esp_err_t ret = xTaskCreate(mqtt_sensor_task, "sensor_data_push_task", 4096, NULL, 3, NULL);
    if (ret != pdPASS)  {
        ESP_LOGE(TAG, "MQTT TCP Start Task Failed");
    }
}