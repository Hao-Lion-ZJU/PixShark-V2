/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : servo.cpp
 * @brief     : 舵机设备驱动文件
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-08-12       Hao Lion        1. <note>
 *******************************************************************************
 * @verbatim :
 *==============================================================================
 *                                                                              
 *                                                                              
 *==============================================================================
 * @endverbatim :
 *****************************Copyright (c) 2023  ZJU****************************
 */

#include "servo/servo.hpp"


AUSServo::AUSServo(serial::Serial* SerialPtr  ,uint8_t id = 0x00)
{
    configASSERT(SerialPtr != nullptr);
    this->SerialPtr_ = SerialPtr;
    this->servo_id = id;
}


/**
  * @brief          计算前n字节累加校验和
  * @param[in]      pch_message: 数据
  * @param[in]      dw_length: 数据和校验的长度
  * @retval         计算完的校验和
  */
uint8_t AUSServo::get_check_sum(uint8_t *pch_message,uint32_t dw_length)
{
   uint8_t check_sum = 0;
    if (pch_message == NULL)
    {
        return 0xFF;
    }
    while(--dw_length)
    {
        check_sum += *pch_message++;
    }
    return check_sum % 256;
}

/**
* @brief     发送内容打包
* @param[in] cmd_type:  命令内容ID
* @param[in] *p_data: 数据段
* @param[in] len:     数据段长度
* @retval			返回要发送的数据大小
*/
uint16_t AUSServo::send_servo_pack(uint8_t cmd_type, uint8_t *p_data, uint8_t len)
{
    memset(servo_tx_buffer, 0, sizeof(servo_tx_buffer));
    uint16_t send_len = 5 + len;
    servo_tx_buffer[0] = HEAD_SOF >> 8;
    servo_tx_buffer[1] = HEAD_SOF & 0xFF;
    servo_tx_buffer[2] = cmd_type;
    servo_tx_buffer[3] = len;
    memcpy(&servo_tx_buffer[4], p_data, len);
    servo_tx_buffer[send_len - 1] =  get_check_sum(servo_tx_buffer, send_len);
    SerialPtr_->write(servo_tx_buffer, send_len);
    return send_len;
}

/**
 * @brief 设置舵机控制角度
 * @param[in] servo_id:   舵机ID
 * @param[in] angle_set:  舵机角度
 * @param[in] time_ms:    舵机运行时间
 * @retval none
*/
void AUSServo::set_servo_angle(int16_t angle_set, uint16_t time_ms)
{
    if(angle_set<=180 && angle_set > -180){
        //单圈模式
        uint8_t data[7];
        data[0] = servo_id;  
        data[1] = (angle_set*10) & 0xff;
        data[2] = (angle_set*10) >> 8;
        data[3] = time_ms & 0xff;
        data[4] = time_ms >> 8;
        data[5] = 0x00;
        data[6] = 0x00;

        send_servo_pack(Angle_set_id, data, sizeof(data));
    }
    else
    {
        //调用多圈模式的函数
        set_servo_angle_multi_turn((int)angle_set,(unsigned int)time_ms);
    }
    

}


/**
 * @brief 设置舵机控制角度
 * @param[in] servo_id:   舵机ID
 * @param[in] angle_set:  舵机角度
 * @retval none
*/
void AUSServo::set_servo_angle(int16_t angle_set)
{
    if(angle_set<=180 && angle_set > -180){
        //单圈模式
        uint16_t time_ms = 500;
        uint8_t data[7];
        data[0] = servo_id;  
        data[1] = (angle_set*10) & 0xff;
        data[2] = (angle_set*10) >> 8;
        data[3] = time_ms & 0xff;
        data[4] = time_ms >> 8;
        data[5] = 0x00;
        data[6] = 0x00;
        
        send_servo_pack(Angle_set_id, data, sizeof(data));
    }
    else
    {
        //调用多圈模式的函数
        set_servo_angle_multi_turn((int)angle_set);
    }
    
}


void AUSServo::set_servo_angle_multi_turn(int angle_set)
{
    unsigned int time_ms = 20000;
    uint8_t data[11];
    data[0] = servo_id;
    //角度
    data[1] = (angle_set*10) & 0xff;
    data[2] = (angle_set*10) >> 8;
    data[3] = (angle_set*10) >> 16;;
    data[4] = (angle_set*10) >> 24;
    data[5] = time_ms & 0xff;
    data[6] = time_ms >> 8;
    data[7] = time_ms >> 16;  
    data[8] = time_ms >> 24;
    data[9] = 0;
    data[10] = 0;
    
    send_servo_pack(Angle_set_multi_id, data, sizeof(data));
}

void AUSServo::set_servo_angle_multi_turn(int angle_set, unsigned int time_ms)
{
    uint8_t data[11];
    data[0] = servo_id;
    //角度
    data[1] = (angle_set*10) & 0xff;
    data[2] = (angle_set*10) >> 8;
    data[3] = (angle_set*10) >> 16;;
    data[4] = (angle_set*10) >> 24;
    data[5] = time_ms & 0xff;
    data[6] = time_ms >> 8;
    data[7] = time_ms >> 16;  
    data[8] = time_ms >> 24;
    data[9] = 0;
    data[10] = 0;
    
    send_servo_pack(Angle_set_multi_id, data, sizeof(data));
}


/**
 * @brief 获取舵机角度
 * @param[in] servo_id:   舵机ID
 * @retval none
*/
int16_t AUSServo::get_servo_angle(void)
{
    uint8_t data[1];
    data[0] = servo_id;  
    send_servo_pack(Angle_get_id, data, sizeof(data));
    return  0;
}

/**
 * @brief 修改舵机ID
 * @param[in] servo_id:   舵机原来ID
 * @param[in] new_id:     舵机新ID
 * @retval none
*/
void AUSServo::modify_servo_id(uint8_t new_id)
{
    uint8_t data[3];
    data[0] = servo_id;  
    data[1] = 0x22; 
    data[2] = new_id; 
    servo_id = new_id;
    send_servo_pack(Modify_Id_id, data, sizeof(data));
}
