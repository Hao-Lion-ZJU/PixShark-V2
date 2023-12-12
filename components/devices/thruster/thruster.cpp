/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : thruster.cpp
 * @brief     : 推进器驱动文件
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-11-1       Hao Lion        1. <note>
 *******************************************************************************
 * @verbatim :
 *==============================================================================
 *                                                                              
 *                                                                              
 *==============================================================================
 * @endverbatim :
 *****************************Copyright (c) 2023  ZJU****************************
 */

#include "thruster/thruster.hpp"



void VESC::set_expect_speed(int32_t speed)
{
    int32_t espeed = speed * THRUSTER_POLAR_PARIS_NUM;  //电转速 = 机械转速 * 极对数
    uint8_t data[4];
    data[3] = espeed & 0xff;
    data[2] = (espeed >> 8) & 0xff;
    data[1] = (espeed >> 16) & 0xff;
    data[0] = (espeed >> 24) & 0xff;
    this->canPtr_->sendto((CAN_PACKET_SET_RPM<<8)|thruster_id_ , data, 4);
}

void VESC::set_expect_current(int32_t current)
{
    uint8_t data[4];
    memcpy(data, &current, sizeof(current));
    this->canPtr_->sendto((CAN_PACKET_SET_CURRENT<<8)|thruster_id_ , data, 4);
}
