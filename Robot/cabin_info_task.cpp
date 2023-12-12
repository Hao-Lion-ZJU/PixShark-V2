/**
  ****************************(C) COPYRIGHT 2022 ZJU****************************
  * @file       cabin_info_task.cpp
  * @brief      舱内各个数据读取任务         
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     OCT-7-2023     HaoLion(郝亮亮)    1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2022 ZJU****************************
  */

#include "common_inc.h"
#include "sht31/sht31.hpp"
#include "adc/adc.hpp"
#include <underwater_robot_msgs/msg/cabin_info.h>

static osThreadId sht31_task_handle;

static void cabin_info_task(void * argument)
{

    cabin_status_t cabin_status;
    //初始化硬件
    //i2c
    I2c i2c(&hi2c4);
    i2c.open();
    SHT31 sht31(&i2c);
    sht31.Init();
    sht31.reset();
    //adc
    Adc adc(&hadc3);
    adc.start();

    //init publisher
    rcl_ret_t rc = 0;
    underwater_robot_msgs__msg__CabinInfo msg;

    for(;;)
    {
        //读取舱内温湿度
        sht31.read_data(cabin_status.cabin_temperature, cabin_status.cabin_humidity);
        uint32_t cpu_temperature_raw_data = adc.read(1);
        cabin_status.cpu_temperature = adc.get_cpu_temprate(cpu_temperature_raw_data);
        //获取实际电压值
        float voltage_vdda_real = 0;
        uint32_t vdda_real_raw_data = adc.read(0);
        voltage_vdda_real = adc.get_real_vdda(vdda_real_raw_data);
        //分压电路所以实际电压值应该×2
        cabin_status.cabin_water_level = 2.0f * (float)(adc.read(2) /FULL_SCALE) * voltage_vdda_real;
        msg.cpu_temperature = cabin_status.cpu_temperature;
        msg.humidity = cabin_status.cabin_humidity;
        msg.temperature = cabin_status.cabin_temperature;
        msg.water_level = cabin_status.cabin_water_level;
        rc = rcl_publish(&cabin_info_publisher, &msg, NULL);
        osDelay(1000);
    }
}




void cabin_info_task_start(void)
{
    const osThreadAttr_t  cabin_infoTask_attributes  = {
    .name = (char*)"cabin_info",
    .stack_size = 256*4,
    .priority = osPriorityNormal,
    };
    sht31_task_handle = osThreadNew(cabin_info_task, NULL, &cabin_infoTask_attributes);
}