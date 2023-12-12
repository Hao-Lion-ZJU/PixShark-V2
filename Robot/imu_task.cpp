/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : imu_task.cpp
 * @brief     : 接收和解析IMU发送过来的数据
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
#include "imu/imu.hpp"
#include "user_lib.h"
#include <sensor_msgs/msg/imu.h>

static osThreadId imu_task_handle;


//The buffer is provided with double capacity to prevent DMA transmission from exceeding the limit
uint8_t imu_rx_buf[2*LPMS::IMU_DATA_LENGTH];

static void imu_task(void  * argument)
{
    //serial init
    serial::Serial imu_serial(&huart3);
    imu_serial.setTimeout(osWaitForever);
    imu_serial.open();
    if(!imu_serial.isOpen())
    {
        configASSERT(0);
    }
    LPMS lpms(&imu_serial);
    lpms.Init();
    imu_data_t imu_data;
    //micro-ros
    rcl_ret_t ret = 0;
    sensor_msgs__msg__Imu imu_msg;
    for(;;)
    {
        //blocing unitl get frame header
        uint8_t ret = imu_serial.read(imu_rx_buf, 1);
        if(ret > 0 && imu_rx_buf[0] == 0x3A)
        {
            //get remain data
            ret = imu_serial.read(imu_rx_buf+1, LPMS::IMU_DATA_LENGTH-1);
            if(ret == LPMS::IMU_DATA_LENGTH-1)
                lpms.imu_data_solve(imu_rx_buf);
            imu_data = lpms.get_imu_data();
            //conversion to quaternion
            float quaternion[4];
            Conversion_Euler_to_Quaternion(quaternion, imu_data.Angle_z, imu_data.Angle_y, imu_data.Angle_x);
            imu_msg.orientation.x = quaternion[0];
            imu_msg.orientation.y = quaternion[1];
            imu_msg.orientation.z = quaternion[2];
            imu_msg.orientation.w = quaternion[3];
            ret = rcl_publish(&imu_publisher, &imu_msg, NULL);
        }   
        memset(imu_rx_buf, 0, 2*LPMS::IMU_DATA_LENGTH);
    }
}

void imu_task_start(void)
{
    const osThreadAttr_t  imuTask_attributes  = {
    .name = (char*)"imu",
    .stack_size = 256*4,
    .priority = osPriorityRealtime,
    };
    imu_task_handle = osThreadNew(imu_task, NULL, &imuTask_attributes);
}