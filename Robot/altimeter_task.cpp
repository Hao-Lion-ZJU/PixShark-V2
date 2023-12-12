/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : altimeter_task.cpp
 * @brief     : 解析高度计发送过来的数据
  * @note       
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-09-28       Hao Lion        1. <note>
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
#include "altimeter/altimeter.hpp"
#include <underwater_robot_msgs/msg/altimeter.h>

static osThreadId altimeter_task_handle;


//The buffer is provided with double capacity to prevent DMA transmission from exceeding the limit
uint8_t altimeter_rx_buf[2*ISA500::AM_DATA_LENGTH];

static void altimeter_task(void  * argument)
{
    //serial init
    serial::Serial altimeter_serial(&huart4);
    altimeter_serial.setTimeout(osWaitForever);
    altimeter_serial.open();
    if(!altimeter_serial.isOpen())
    {
        configASSERT(0);
    }
    ISA500 isa500(&altimeter_serial);
    isa500.Init();
    //micro-ros
    rcl_ret_t ret = 0;
    underwater_robot_msgs__msg__Altimeter altimeter_msg;
    for(;;)
    {
        //blocing unitl buffer is fill or get the <LF>
        altimeter_serial.readline(altimeter_rx_buf, 2*ISA500::AM_DATA_LENGTH);
        isa500.altimeter_data_solve(altimeter_rx_buf);
        altimeter_msg.height = isa500.get_altimeter_data();
        ret = rcl_publish(&altimeter_publisher, &altimeter_msg, NULL);
        memset(altimeter_rx_buf, 0, 2*ISA500::AM_DATA_LENGTH);
    }
}

void altimeter_task_start(void)
{
    const osThreadAttr_t  altimeterTask_attributes  = {
    .name = (char*)"altimeter",
    .stack_size = 256*4,
    .priority = osPriorityRealtime,
    };
    altimeter_task_handle = osThreadNew(altimeter_task, NULL, &altimeterTask_attributes);
}