/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : subscription_task.cpp
 * @brief     : 处理订阅话题任务
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-12-11       Hao Lion        1. <note>
 *******************************************************************************
 * @verbatim :
 *==============================================================================
 *                                                                              
 *                                                                              
 *==============================================================================
 * @endverbatim :
 *****************************Copyright (c) 2023  ZJU****************************
 */

#include "common_inc.h"
#include <std_msgs/msg/int16_multi_array.h>
#include <std_msgs/msg/int16.h>

static osThreadId subscription_task_handle;

// void (* rclc_subscription_callback_t)(const void *);
// Implementation example:
void thruster_sub_callback(const void * msgin)
{
    if(msgin != NULL)
    {
        // Cast received message to used type
        // const std_msgs__msg__Int16MultiArray * msg = (const std_msgs__msg__Int16MultiArray *)msgin;
        // for(int i=0; i< (msg->data.size); i++)
        // {
        //     thruster_speed[i] = msg->data.data[i];
        // }
    }
    
}

void crawler_sub_callback(const void * msgin)
{
    if(msgin != NULL)
    {
        xTaskNotifyGive((TaskHandle_t)crawler_task_handle);
    }
    
}


static void subscription_task(void  * argument)
{

    thruster_task_start();
    std_msgs__msg__Int16MultiArray thruster_msg;
    std_msgs__msg__Int16MultiArray__init(&thruster_msg);
    thruster_msg.data.size = THRUSTER_NUM;
    thruster_msg.data.capacity = THRUSTER_NUM*sizeof(int16_t);
    thruster_msg.data.data = thruster_speed;
    rcl_ret_t rc = rclc_executor_add_subscription(
    &sub_executor, &thruster_subscriber, &thruster_msg,
    &thruster_sub_callback, ON_NEW_DATA);
    if (rc != RCL_RET_OK) {
        printf("Error in rclc_executor_add_subscription. \n");
    }

    #if CRAWLER_NUM
    crawler_task_start();
    std_msgs__msg__Int16MultiArray crawler_msg;
    std_msgs__msg__Int16MultiArray__init(&crawler_msg);
    crawler.data.size = CRAWLER_NUM;
    crawler.data.capacity = CRAWLER_NUM*sizeof(int16_t);
    crawler.data.data = crawler_speed;
    #endif
    for(;;)
    {
        osDelay(10);
        rclc_executor_spin_some(&sub_executor, 10*(1000*1000));
    }
}

void subscription_task_start(void)
{
    const osThreadAttr_t  subscriptionTask_attributes  = {
    .name = (char*)"subscription",
    .stack_size = 512*4,
    .priority = osPriorityNormal,
    };
    subscription_task_handle = osThreadNew(subscription_task, NULL, &subscriptionTask_attributes);
}