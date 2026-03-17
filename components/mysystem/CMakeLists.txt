idf_component_register(
    SRCS "StateMachine.cpp"
    INCLUDE_DIRS "."
    REQUIRES 
        esp_common
        freertos
        network
        sensor
        device
)