#pragma once

#include <memory>

/* 前向声明，避免头文件耦合 */
class WifiManager;
class MQTTClient;
class SensorManager;
class DeviceController;

/* 系统状态 */
enum class SystemState
{
    SYSTEM_INIT = 0,
    WIFI_CONNECT,
    MQTT_CONNECT,
    SYSTEM_RUNNING,
    ERROR_RECOVERY
};

class StateMachine
{
private:

    SystemState state;

    WifiManager* wifi;
    MQTTClient* mqtt;
    SensorManager* sensor;
    DeviceController* device;

public:

    StateMachine(
        WifiManager* wifi,
        MQTTClient* mqtt,
        SensorManager* sensor,
        DeviceController* device
    );

    void run();

private:

    void handleInit();
    void handleWifiConnect();
    void handleMQTTConnect();
    void handleRunning();
    void handleError();
};
