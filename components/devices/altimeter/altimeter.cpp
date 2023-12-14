/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : altimeter.cpp
 * @brief     : 高度计设备驱动文件
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-08-14         WPJ        1. <note>
 *******************************************************************************
 * @verbatim :
 *==============================================================================
 * 高度计数据读取通过上位机设置为定时发送
 * 指令ID122
 * 返回数据帧格式为：ddd.ddd\r\n (直接是字符串形式ASCII码)                                        
 *==============================================================================
 * @endverbatim :
 *****************************Copyright (c) 2023  ZJU****************************
 */


#include "altimeter/altimeter.hpp"

/**
 * @brief Altimeter基类的构造函数，初始化Altimeter_data
 * @retval none
*/
Altimeter::Altimeter(){
    memset(&altimeter_data,0,sizeof(altimeter_data));
}


/**
 * @brief ISA500构造函数
*/
ISA500::ISA500(serial::Serial *serialPtr)
{
    configASSERT(serialPtr != nullptr);
    this->SerialPtr_ = serialPtr;
}


/**
  * @brief          高度计协议解析
  * @param[in]      am_frame: 原生数据指针
  * @param[in]     am_data: 高度计数据指针
  * @retval         none
  */
void ISA500::altimeter_data_solve(volatile const uint8_t *am_frame)
{
	/*数据校验*/
    if (am_frame == NULL)
    {
        return;
    }
    //TODO:进行高度计数据解析
    this->altimeter_data = atof((char *)am_frame);
}

/**
 * @brief P30构造函数
*/
P30::P30(serial::Serial *serialPtr)
{
    configASSERT(serialPtr != nullptr);
    this->SerialPtr_ = serialPtr;
}

/**
  * @brief          高度计协议解析
  * @param[in]      am_frame: 原生数据指针
  * @retval         none
  */
void P30::altimeter_data_solve(volatile const uint8_t *am_frame)
{
    uint16_t psum = 0;
    if(am_frame[0] == 0x42 && am_frame[1] == 0x52)
    {
        for(int i = 0; i<13 ; i++)
        {
            psum = psum + am_frame[i];
        }
        if((psum&0xff)==am_frame[13] && (psum>>8)==am_frame[14])
        {
            this->altimeter_data = am_frame[8]|(am_frame[9]<<8)|(am_frame[10]<<16)|(am_frame[11]<<24);
        }
    }
}

/**
 * @brief          请求读取一次高度值
 * @param[in]      none
 * @return  	   none
*/
void P30::request_data(void)
{
    this->cmd_tx_buf[0]=0x42;//填充发送缓冲区
    this->cmd_tx_buf[1]=0x52;//填充发送缓冲区
    this->cmd_tx_buf[2]=0x00;//填充发送缓冲区
    this->cmd_tx_buf[3]=0x00;//填充发送缓冲区
    this->cmd_tx_buf[4]=0xBB;//填充发送缓冲区
    this->cmd_tx_buf[5]=0x04;//填充发送缓冲区
    this->cmd_tx_buf[6]=0x00;//填充发送缓冲区
    this->cmd_tx_buf[7]=0x00;//填充发送缓冲区
    this->cmd_tx_buf[8]=0x53;//填充发送缓冲区
    this->cmd_tx_buf[9]=0x01;//填充发送缓冲区
    this->SerialPtr_->write(cmd_tx_buf, 10);
}