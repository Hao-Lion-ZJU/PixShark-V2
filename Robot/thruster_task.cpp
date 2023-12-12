/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : thruster_task.cpp
 * @brief     : 推进器执行任务
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-10-21       Hao Lion        1. <note>
 *******************************************************************************
 * @verbatim :
 *==============================================================================
 *                                                                              
 *                                                                              
 *==============================================================================
 * @endverbatim :
 *****************************Copyright (c) 2023  ZJU****************************
 */

#include "thruster_task.hpp"
#include "thruster/thruster.hpp"


osThreadId thruster_task_handle;
#define THRUSTER_CONTROL_PERIOD_MS 5

int16_t thruster_speed[THRUSTER_NUM];

Can* thrutser_canPtr = nullptr;
VESC* vescesPtr = nullptr;

void thruster_init()
{
    //初始化can
    thrutser_canPtr = new Can(&hfdcan1);
    thrutser_canPtr->start();
    vescesPtr = new VESC[THRUSTER_NUM]{
    VESC(thrutser_canPtr,Thruster_Vertical_Left_ID),
    VESC(thrutser_canPtr,Thruster_Vertical_Right_ID),
    VESC(thrutser_canPtr,Thruster_Horizontal_TopLeft_ID),
    VESC(thrutser_canPtr,Thruster_Horizontal_TopRight_ID),
    VESC(thrutser_canPtr,Thruster_Horizontal_BottomRight_ID),
    VESC(thrutser_canPtr,Thruster_Horizontal_BottomLeft_ID)
    };
    for(int i =0 ; i < THRUSTER_NUM; i++)
    {
        vescesPtr[i].Init();
    }
}

static void thruster_task(void * argument)
{
    //初始化thruster
    thruster_init();
    uint8_t current_brightness_level = 0;  //当前barlus灯光亮度档位
    for(;;)
    {
        for(int i =0 ; i < THRUSTER_NUM; i++)
        {
            osDelay(THRUSTER_CONTROL_PERIOD_MS);
            vescesPtr[i].set_expect_speed(thruster_speed[i]);//;
        }
    }
    

}



void thruster_task_start(void)
{
    const osThreadAttr_t  thrusterTask_attributes  = {
    .name = (char*)"thruster",
    .stack_size = 128,
    .priority = osPriorityNormal,
    };
    thruster_task_handle = osThreadNew(thruster_task, NULL, &thrusterTask_attributes);
}