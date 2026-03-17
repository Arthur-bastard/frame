idf_component_register(
    SRCS "WifiManager.cpp" "MQTTClient.cpp"
    INCLUDE_DIRS "."
    REQUIRES 
        esp_common
        esp_wifi 
        nvs_flash
        esp_event
        mqtt
        json
    PRIV_REQUIRES
        sensor
)