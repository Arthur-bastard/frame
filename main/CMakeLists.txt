idf_component_register(
    SRCS "main.cpp"
    INCLUDE_DIRS "."
    REQUIRES 
        nvs_flash 
        esp_wifi 
        esp_event 
        esp_system
        esp_netif
        mysystem
        network
        sensor
        device
        esp_common
        mqtt
        )