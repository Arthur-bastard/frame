#include "DeviceController.hpp"

#include "esp_log.h"

static const char* TAG = "DeviceController";

DeviceController::DeviceController()
{
}

void DeviceController::init()
{
    ESP_LOGI(TAG, "DeviceController init");
}

void DeviceController::update()
{
    ESP_LOGI(TAG, "DeviceController update");
}