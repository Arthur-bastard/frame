#pragma once

#include "esp_wifi.h"
#include "esp_event.h"

class WifiManager
{
public:

    WifiManager();

    bool connect();

    bool isConnected();

private:

    static void wifi_event_handler(
        void* arg,
        esp_event_base_t event_base,
        int32_t event_id,
        void* event_data
    );

    static bool connected;
};