/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : param_task.cpp
 * @brief     : 处理参数服务器任务
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
#include "RobotConfig.h"

static osThreadId param_task_handle;


bool on_parameter_changed(const Parameter * old_param, const Parameter * new_param, void * context)
{
  (void) context;
    rcl_ret_t rc = 0;
  if (old_param == NULL && new_param == NULL) {
    printf("Callback error, both parameters are NULL\n");
    return false;
  }
  if(strcmp(new_param->name.data, LED_PARAM)==0)
  {
    led_brihtness = new_param->value.integer_value;
    xTaskNotifyGive((TaskHandle_t)led_task_handle);
  }
  else if(strcmp(new_param->name.data, SERVO_PARAM)==0)
  {
    servo_angle = new_param->value.integer_value;
    xTaskNotifyGive((TaskHandle_t)servo_task_handle);
  }
  return true;
}

static void param_task(void  * argument)
{
    led_task_start();
    servo_task_start();
    rcl_ret_t rc = rclc_add_parameter(&param_server, LED_PARAM, RCLC_PARAMETER_INT);
    // Set parameter value
    rc = rclc_parameter_set_int(&param_server,LED_PARAM , 100);
    rc = rclc_add_parameter(&param_server, SERVO_PARAM, RCLC_PARAMETER_INT);
    // Set parameter value
    rc = rclc_parameter_set_int(&param_server, SERVO_PARAM, 20);
    rc = rclc_executor_add_parameter_server(&param_executor, &param_server, on_parameter_changed);
    for(;;)
    {
        osDelay(100);
        rclc_executor_spin_some(&param_executor, 100*(1000*1000));
    }
}

void param_task_start(void)
{
    const osThreadAttr_t  paramTask_attributes  = {
    .name = (char*)"param",
    .stack_size = 512*4,
    .priority = osPriorityNormal,
    };
    param_task_handle = osThreadNew(param_task, NULL, &paramTask_attributes);
}