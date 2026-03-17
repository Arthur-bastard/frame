#pragma once

#include "mqtt_client.h"
#include "SensorData.hpp"

class MQTTClient
{

public:

    MQTTClient();

    bool connect();

    void publishSensorData(const SensorData& data);

private:

    esp_mqtt_client_handle_t client;

    static void mqtt_event_handler(
        void* handler_args,
        esp_event_base_t base,
        int32_t event_id,
        void* event_data
    );
};