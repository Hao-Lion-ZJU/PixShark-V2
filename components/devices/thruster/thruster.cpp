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

void FUBER::thruster_init(void)
{
    cmd_control(0, 0xAA);
}

void FUBER::cmd_control(int16_t velocity, uint8_t ACK_MODE)
{
    int16_t speed;
    memset(thrust_tx_buffer, 0, sizeof(thrust_tx_buffer));
    if(velocity > 0)
    {
        speed = velocity;
        speed = speed < max_speed? speed: max_speed;
        thrust_tx_buffer[0] = 0x01; //开启电机
        thrust_tx_buffer[1] = 0x00; //电机正转
    }
    else if(velocity == 0)
    {
        speed = velocity;
        thrust_tx_buffer[0] = 0x01; //开启电机
        thrust_tx_buffer[1] = 0x00;
    }
    else
    {
        speed = -velocity;
        speed = speed < max_speed? speed: max_speed;
        thrust_tx_buffer[0] = 0x01; //开启电机
        thrust_tx_buffer[1] = 0x01; //电机反转
    }
    thrust_tx_buffer[2] = (speed >> 8);
    thrust_tx_buffer[3] = speed;
    thrust_tx_buffer[7] = ACK_MODE;

    this->canPtr_->sendto(thruster_id_ + CAN_ID_BASE,thrust_tx_buffer, 8);
}

void FUBER::set_controler(controller_param_set_e _param, uint16_t value)
{
    thrust_tx_buffer[0] = (_param >> 8);
    thrust_tx_buffer[1] = _param;
    thrust_tx_buffer[2] = (value >> 8);
    thrust_tx_buffer[3] = value;

    this->canPtr_->sendto(CAN_CONTROL_PARAM_ID, thrust_tx_buffer, 4);
}

void FUBER::param_request(void)
{
    thrust_tx_buffer[0] = 0x00;
    thrust_tx_buffer[1] = 0x00;
    
    this->canPtr_->sendto(CAN_MOTOR_PARAM_REQUEST_ID + thruster_id_, thrust_tx_buffer, 2);
}

void FUBER::thrust_status_get(void)
{
    uint32_t can_id;
    uint32_t id_type;
    uint8_t can_type;
    uint8_t rx_data[8];
    uint32_t thruster_index;
    uint16_t Motor_Status;
    this->canPtr_->recvfrom(can_id, id_type, rx_data);
    
    can_type = can_id >> 4;
    thruster_index = can_id & 0x0f - 0x02;
    if(thruster_index > 6 || thruster_index != thruster_id_)
    {
        return;
    }

    switch(can_type)
    {
        case CAN_RETURN_ID:
        {
            Motor_Status = rx_data[0] << 8 | rx_data[1];
            if(Motor_Status == 0x0000)
            {
                motor_param_t.motor_status = THRUSTER_OK;
            }
            else
            {
                motor_param_t.motor_status = THRUSTER_FAULT;
            }
            break;
        }
        case CAN_MOTOR_PARAM_ID:
        {
            motor_param_t.speed_rpm = (uint16_t)((rx_data)[0] << 8 | (rx_data)[1]);      
            motor_param_t.given_voltage = ((float)((rx_data)[2] << 8 | (rx_data)[3])/10);  
            motor_param_t.given_current = ((float)((rx_data)[4] << 8 | (rx_data)[5])/10);  
            motor_param_t.controller_temperate = ((rx_data)[6]-50);                        
            motor_param_t.motor_temperate = ((rx_data)[7]-50);
            break; 	
        }
        default: break;
    }
}
