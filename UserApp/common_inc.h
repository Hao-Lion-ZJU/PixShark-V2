#ifndef _COMMON_INC_H_
#define _COMMON_INC_H_

/*---------------------------- C Scope ---------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <uxr/client/transport.h>
#include <rmw_microxrcedds_c/config.h>
#include <rmw_microros/rmw_microros.h>
#include <rclc_parameter/rclc_parameter.h>

void Main(void);

extern rcl_publisher_t cabin_info_publisher;
extern rcl_publisher_t altimeter_publisher;
extern rcl_publisher_t depth_publisher;  
extern rcl_publisher_t imu_publisher;  
extern rclc_parameter_server_t param_server;
extern rclc_executor_t param_executor;

extern rcl_subscription_t thruster_subscriber;
extern rcl_subscription_t crawler_subscriber;
extern rclc_executor_t sub_executor;

#ifdef __cplusplus
}

/*---------------------------- C++ Scope ---------------------------*/
#include "common.hpp"
#include "cabin_info_task.hpp"
#include "altimeter_task.hpp"
#include "led_task.hpp"
#include "servo_task.hpp"
#include "param_task.hpp"
#include "subscription_task.hpp"

#endif
#endif //_COMMON_INC_H_
