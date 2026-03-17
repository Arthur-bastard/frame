#include "MQTTClient.hpp"

#include "esp_log.h"
#include "cJSON.h"

static const char* TAG = "MQTT";

static const char* BROKER_URI = "mqtt://bemfa.com";

MQTTClient::MQTTClient()
{
    client = nullptr;
}

bool MQTTClient::connect()
{

    esp_mqtt_client_config_t mqtt_cfg = {};

    mqtt_cfg.broker.address.uri = BROKER_URI;

    client = esp_mqtt_client_init(&mqtt_cfg);

    esp_mqtt_client_register_event(
        client,
        MQTT_EVENT_ANY,
        mqtt_event_handler,
        this
    );

    esp_mqtt_client_start(client);

    ESP_LOGI(TAG,"MQTT start");

    return true;
}

void MQTTClient::mqtt_event_handler(
    void* handler_args,
    esp_event_base_t base,
    int32_t event_id,
    void* event_data)
{

    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;

    switch(event->event_id)
    {

        case MQTT_EVENT_CONNECTED:

            ESP_LOGI(TAG,"MQTT connected");

            esp_mqtt_client_subscribe(
                event->client,
                "smartfarm/cmd",
                0
            );

        break;

        case MQTT_EVENT_DATA:

            ESP_LOGI(TAG,"MQTT DATA");

        break;

        default:

        break;
    }
}

void MQTTClient::publishSensorData(const SensorData& data)
{

    if(client == nullptr)
        return;

    cJSON* root = cJSON_CreateObject();

    cJSON_AddNumberToObject(root,"temp",data.temperature);
    cJSON_AddNumberToObject(root,"hum",data.humidity);
    cJSON_AddNumberToObject(root,"light",data.light);
    cJSON_AddNumberToObject(root,"co2",data.co2);

    char* json = cJSON_PrintUnformatted(root);

    esp_mqtt_client_publish(
        client,
        "smartfarm/sensor",
        json,
        0,
        1,
        0
    );

    cJSON_Delete(root);
    free(json);
}