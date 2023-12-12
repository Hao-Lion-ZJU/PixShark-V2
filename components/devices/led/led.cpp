/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : led.cpp
 * @brief     : LED设备驱动文件
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


#include "led/led.hpp"



Barlus::Barlus(serial::Serial *serialPtr)
{
    configASSERT(serialPtr != nullptr);
    this->SerialPtr_ = serialPtr;
    led_tx_buffer[0] = 0xFF;
    led_tx_buffer[1] = 0x01;
    led_tx_buffer[2] = 0x00;
    led_tx_buffer[3] = 0x07;
    led_tx_buffer[4] = 0x00;
    led_tx_buffer[5] = 0x00;
    led_tx_buffer[6] = 0x00;
}



/**
 * @brief 手动关闭LED灯
 * @param none
 * @retval none
*/
void Barlus::off(void)
{
    led_tx_buffer[5] = 0x99;
    led_tx_buffer[6] = 0xA1;

    SerialPtr_->write(led_tx_buffer, sizeof(led_tx_buffer));
}


/**
 * @brief 灯光增强
 * @param none
 * @retval none
*/
void Barlus::enhance(void)
{

    led_tx_buffer[5] = 0x96;
    led_tx_buffer[6] = 0x9E;

    SerialPtr_->write(led_tx_buffer, sizeof(led_tx_buffer));
}

/**
 * @brief 灯光减弱
 * @param none
 * @retval none
*/
void Barlus::weaken(void)
{

    led_tx_buffer[5] = 0x97;
    led_tx_buffer[6] = 0x9F;

    SerialPtr_->write(led_tx_buffer, sizeof(led_tx_buffer));
}

/**
 * @brief 灯光亮度存储
 * @param none
 * @retval none
*/
void Barlus::save(void)
{
    led_tx_buffer[5] = 0xFA;
    led_tx_buffer[6] = 0x02;

    SerialPtr_->write(led_tx_buffer, sizeof(led_tx_buffer));
}

/**
 * @brief 灯光亮度恢复
 * @param none
 * @retval none
*/
void Barlus::recover(void)
{
    led_tx_buffer[5] = 0xFB;
    led_tx_buffer[6] = 0x03;

    SerialPtr_->write(led_tx_buffer, sizeof(led_tx_buffer));
}

void Barlus::on(uint8_t brightness)
{
    
    
}
