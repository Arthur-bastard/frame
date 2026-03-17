#include "StateMachine.hpp"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* 引入模块头 */
#include "WifiManager.hpp"
#include "MQTTClient.hpp"
#include "SensorManager.hpp"
#include "DeviceController.hpp"

static const char* TAG = "STATE_MACHINE";

StateMachine::StateMachine(
    WifiManager* wifi,
    MQTTClient* mqtt,
    SensorManager* sensor,
    DeviceController* device)
{
    this->wifi = wifi;
    this->mqtt = mqtt;
    this->sensor = sensor;
    this->device = device;

    state = SystemState::SYSTEM_INIT;
}

void StateMachine::run()
{
    switch(state)
    {
        case SystemState::SYSTEM_INIT:
            handleInit();
            break;

        case SystemState::WIFI_CONNECT:
            handleWifiConnect();
            break;

        case SystemState::MQTT_CONNECT:
            handleMQTTConnect();
            break;

        case SystemState::SYSTEM_RUNNING:
            handleRunning();
            break;

        case SystemState::ERROR_RECOVERY:
            handleError();
            break;
    }
}

/* 系统初始化 */

void StateMachine::handleInit()
{
    ESP_LOGI(TAG,"SYSTEM INIT");

    sensor->init();
    device->init();

    state = SystemState::WIFI_CONNECT;
}

/* WiFi连接 */

void StateMachine::handleWifiConnect()
{
    ESP_LOGI(TAG,"Connecting WiFi");

    if(wifi->connect())
    {
        state = SystemState::MQTT_CONNECT;
    }
    else
    {
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

/* MQTT连接 */

void StateMachine::handleMQTTConnect()
{
    ESP_LOGI(TAG,"Connecting MQTT");

    if(mqtt->connect())
    {
        state = SystemState::SYSTEM_RUNNING;
    }
    else
    {
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

/* 系统运行 */

void StateMachine::handleRunning()
{
    sensor->update();

    auto data = sensor->getData();

    mqtt->publishSensorData(data);

    device->update();

    vTaskDelay(pdMS_TO_TICKS(3000));
}

/* 异常恢复 */

void StateMachine::handleError()
{
    ESP_LOGE(TAG,"System Error Recovery");

    state = SystemState::WIFI_CONNECT;
}