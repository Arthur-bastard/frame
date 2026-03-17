#pragma once

#include "SensorData.hpp"

class SensorManager
{

public:

    SensorManager();

    /* 初始化所有传感器 */
    void init();

    /* 更新传感器数据 */
    void update();

    /* 获取传感器数据 */
    SensorData getData();

private:

    SensorData data;

};