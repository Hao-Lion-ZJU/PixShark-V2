/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : main.cpp
 * @brief     : 用户自定义主函数，会被freertos调用，无需关心原来的c文件，专注上层即可
 * @note      : micro-ros建立的包并不是多线程的，所以所有的话题、服务、参数都是在Main
 *              线程里面创建，开启了共享内存使得其他任务可以访问这些话题、服务、参数
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-10-01       Hao Lion        1. <note>
 *  V2.0.0    2023-12-11       Hao Lion        1. 修改为ros2形式
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
#include "RobotConfig.h"
#include <underwater_robot_msgs/msg/cabin_info.h>
#include <underwater_robot_msgs/msg/altimeter.h>
#include <sensor_msgs/msg/imu.h>
#include <std_msgs/msg/int16.h>
#include <std_msgs/msg/int16_multi_array.h>

  
rcl_publisher_t cabin_info_publisher;
rcl_publisher_t altimeter_publisher;
rcl_publisher_t depth_publisher;
rcl_publisher_t imu_publisher;
rclc_parameter_server_t param_server;
rclc_executor_t param_executor;
rcl_subscription_t thruster_subscriber;
rcl_subscription_t crawler_subscriber;
rclc_executor_t sub_executor;

/* Default Entry -------------------------------------------------------*/

void Main(void)
{
    rcl_allocator_t allocator;
    allocator = rcl_get_default_allocator();
    //create init_options
    rclc_support_t support; 
    rcl_node_t node;
    rcl_ret_t ret = 0;
    //broke unitl success
    do
    {
        ret =  rclc_support_init(&support, 0, NULL, &allocator);
        osDelay(1000);
    } while (ret != RCL_RET_OK);
    ret = rclc_node_init_default(&node, "mcu_node", "", &support);
    if (ret != RCL_RET_OK)
    {
      HAL_NVIC_SystemReset();
    }
    rclc_publisher_init_best_effort(
    &cabin_info_publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(underwater_robot_msgs, msg, CabinInfo),
    CABIN_INFO_TOPIC);
    rclc_publisher_init_best_effort(
    &altimeter_publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(underwater_robot_msgs, msg, Altimeter),
    ALTIMETER_TOPIC);
    rclc_publisher_init_best_effort(
    &imu_publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, Imu),
    IMU_TOPIC);

    // Initialize parameter server options
    const rclc_parameter_options_t options = {
    .notify_changed_over_dds = true,
    .max_params = 4,
    .allow_undeclared_parameters = true,
    .low_mem_mode = false
    };

    // Initialize parameter server with configured options
    ret = rclc_parameter_server_init_with_option(&param_server, &node, &options);
    param_executor = rclc_executor_get_zero_initialized_executor();
    rclc_executor_init(&param_executor, &support.context, RCLC_EXECUTOR_PARAMETER_SERVER_HANDLES, &allocator);

    unsigned int num_handles = 1;
    thruster_subscriber = rcl_get_zero_initialized_subscription();
    rcl_subscription_options_t thruster_subscription_options = rcl_subscription_get_default_options();
    thruster_subscription_options.qos.depth = 0; // qos: last is best = register semantics
    ret = rcl_subscription_init(&thruster_subscriber, &node, 
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int16MultiArray),
    THRUSTER_TOPIC,
    &thruster_subscription_options);

    #if CRAWLER_NUM
    num_handles++;
    crawler_subscriber = rcl_get_zero_initialized_subscription();
    rcl_subscription_options_t crawler_subscription_options = rcl_subscription_get_default_options();
    crawler_subscription_options.qos.depth = 0; // qos: last is best = register semantics
    ret = rcl_subscription_init(&crawler_subscriber, &node, 
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int16MultiArray),
    CRAWLER_TOPIC,
    &crawler_subscription_options);
    #endif
    
    sub_executor = rclc_executor_get_zero_initialized_executor();
    rclc_executor_init(&sub_executor, &support.context, num_handles, &allocator);


    cabin_info_task_start();
    altimeter_task_start();
    imu_task_start();
    param_task_start();
    subscription_task_start();
    for(;;)
    {
      osDelay(100);
    }
    
}
