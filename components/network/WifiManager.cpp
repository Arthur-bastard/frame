#include "WifiManager.hpp"

#include "esp_log.h"
#include "nvs_flash.h"
#include <string.h> 
#include <esp_mac.h>
static const char* TAG = "WiFi";

bool WifiManager::connected = false;

WifiManager::WifiManager()
{
}

bool WifiManager::connect()
{
    ESP_LOGI(TAG,"Initializing WiFi");

    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    esp_wifi_init(&cfg);

    esp_event_handler_instance_register(
        WIFI_EVENT,
        ESP_EVENT_ANY_ID,
        &wifi_event_handler,
        NULL,
        NULL
    );

    esp_event_handler_instance_register(
        IP_EVENT,
        IP_EVENT_STA_GOT_IP,
        &wifi_event_handler,
        NULL,
        NULL
    );

    wifi_config_t wifi_config = {};

    strcpy((char*)wifi_config.sta.ssid, "ssid");
    strcpy((char*)wifi_config.sta.password, "password");

    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);

    esp_wifi_start();

    ESP_LOGI(TAG,"WiFi started");

    return true;
}

void WifiManager::wifi_event_handler(
    void* arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void* event_data)
{

    if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect();
    }

    else if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        connected = false;

        ESP_LOGW(TAG,"WiFi disconnected, reconnecting...");

        esp_wifi_connect();
    }

    else if(event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        connected = true;

        ESP_LOGI(TAG,"WiFi connected");
    }
}

bool WifiManager::isConnected()
{
    return connected;
}