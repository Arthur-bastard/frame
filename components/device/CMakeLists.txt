idf_component_register(
    SRCS "DeviceController.cpp"
    INCLUDE_DIRS "."
    REQUIRES 
        driver
        esp_common
)