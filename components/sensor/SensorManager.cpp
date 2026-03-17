#include "SensorManager.hpp"

#include "esp_log.h"

static const char* TAG = "SensorManager";

SensorManager::SensorManager()
{
}

void SensorManager::init()
{
    ESP_LOGI(TAG, "SensorManager init");
}

void SensorManager::update()
{
    ESP_LOGI(TAG, "SensorManager update");

    /* 模拟数据 */

    data.temperature = 25.0;
    data.humidity = 60.0;
    data.light = 300;
    data.co2 = 500;
}

SensorData SensorManager::getData()
{
    return data;
}