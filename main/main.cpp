#include "StateMachine.hpp"
#include "SensorManager.hpp"
#include "DeviceController.hpp"
#include "MQTTClient.hpp"
#include "WifiManager.hpp"
#include "mqtt_client.h"

extern "C"
{
#include "nvs_flash.h"
}

SensorManager sensor;
DeviceController device;
MQTTClient mqtt;
WifiManager wifi;

StateMachine systemCore(
    &wifi,
    &mqtt,
    &sensor,
    &device
);

extern "C" void app_main()
{
    nvs_flash_init();

    while(true)
    {
        systemCore.run();
    }
}