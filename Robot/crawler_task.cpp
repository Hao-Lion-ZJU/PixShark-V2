/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : crawler_task.cpp
 * @brief     : 履带电机执行任务
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


#include "crawler_task.hpp"
#include "crawler/crawler.hpp"
#include "RobotConfig.h"

osThreadId crawler_task_handle;

#if CRAWLER_NUM

Can* crawler_canPtr = nullptr;
GIANT* giantsPtr = nullptr;
int16_t crawler_speed[CRAWLER_NUM];

void crawler_init()
{
    //初始化can
    crawler_canPtr = new Can(&hfdcan1);
    crawler_canPtr->start();
    giantsPtr = new GIANT[CRAWLER_NUM]{
    GIANT(crawler_canPtr,Crawler_Left_ID),
    GIANT(crawler_canPtr,Crawler_Right_ID)
    };
    for(int i =0 ; i < CRAWLER_NUM; i++)
    {
        giantsPtr[i].Init();
    }
}

/**
 * @brief          履带电机执行任务
 * @param[in]      argument: Not used
 * @retval         None
*/
static void crawler_task(void * argument)
{
    crawler_init();
    for(;;)
    {
        //等待控制指令
        while (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) != pdPASS)
        {
        }
        for(int i =0 ; i < CRAWLER_NUM; i++)
        {
            giantsPtr[i].set_expect_speed(crawler_speed[i]);
        }
        
    }
}




void crawler_task_start(void)
{
    const osThreadAttr_t  crawlerTask_attributes  = {
    .name = (char*)"crawler",
    .stack_size = 128,
    .priority = osPriorityNormal,
    };
    crawler_task_handle = osThreadNew(crawler_task, NULL, &crawlerTask_attributes);
}

#endif