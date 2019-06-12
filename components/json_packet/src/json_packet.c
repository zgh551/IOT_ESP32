#include "json_packet.h"

static const char *TAG = "json packet";

void SensorPushPacket(char * s)
{
    cJSON *p_root = cJSON_CreateObject();
    cJSON_AddStringToObject(p_root,"t","up");
    cJSON_AddObjectToObject(p_root,"obj");
    char *sd = cJSON_Print(p_root);
    sprintf(s,sd);
    cJSON_free((void *)sd);
    ESP_LOGI(TAG,"Push Sensor Data Packet:\r\n %s",s);
    cJSON_Delete(p_root);
}

void AckPushPacket(uint32_t id,uint32_t led_value,char * s)
{
    cJSON *p_root = cJSON_CreateObject();
    cJSON_AddNumberToObject(p_root,"mid",id);
    cJSON_AddStringToObject(p_root,"t","rp");
    cJSON *led_s = cJSON_CreateObject();
    cJSON_AddNumberToObject(led_s,"led",led_value);
    cJSON_AddItemToObject(p_root,"obj",led_s); 
    char *sd = cJSON_Print(p_root);
    sprintf(s,sd);
    cJSON_free((void *)sd);
    ESP_LOGI(TAG,"Push Ack Packet:\r\n %s",s);
    cJSON_Delete(p_root);
}

int8_t SwitchPacketParse(char * s,uint32_t *id,uint32_t *led_value)
{
    cJSON *monitor_json = cJSON_Parse(s);   
    if(monitor_json != NULL)
    {
        cJSON *mid_r = cJSON_GetObjectItem(monitor_json, "mid");
        cJSON *obj_r = cJSON_GetObjectItem(monitor_json, "obj");
        cJSON *led_r = cJSON_GetObjectItem(obj_r, "led");
        if(cJSON_IsNumber(mid_r) && cJSON_IsNumber(led_r))
        {
            ESP_LOGI(TAG,"receive mid:%d;led:%d",mid_r->valueint,led_r->valueint);
            *id = mid_r->valueint;
            *led_value = led_r->valueint;
            cJSON_Delete(monitor_json);
            return 0;
        }
        else
        {
            cJSON_Delete(monitor_json);
            return -1;
        }
    }
    else
    {
        cJSON_Delete(monitor_json);
        return -1;
    }
}


