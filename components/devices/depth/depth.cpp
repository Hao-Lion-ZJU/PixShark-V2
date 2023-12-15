/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : depth.cpp
 * @brief     : 深度计设备驱动文件
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-08-14         WPJ        1. <note>
 *  V1.0.1    2023-9-30          Hao Lion   1. 重构为c++类
 *******************************************************************************
 * @verbatim :
 *==============================================================================
 * 深度计的数据读取————————中断读取                                                                             
 * 深度计数据解析——————————需要发送指令才能得到回传                                                   
 *==============================================================================
 * @endverbatim :
 *****************************Copyright (c) 2023  ZJU****************************
 */


#include "depth/depth.hpp"
#include "crc/CRC8_CRC16.h"

#define WATER_DENSITY 	    1000.0f
#define g 	                9.8f

/**
 * @brief 深度计基类的构造函数，初始化depth_data
 * @retval none
*/
Depth::Depth(){
    memset(&depth_data,0,sizeof(depth_data));
}



/**
 * @brief          深度计协议解析，直接读取压力值，不进行modbus协议解析
 * @param[in]      depth_frame: 原生数据指针
 * @return  	   none
*/
void KELLER::depth_data_solve(volatile const uint8_t *depth_frame)
{
  static int i = 5;
  static float sum = 0;
  float pressure1 = 0;
	/*数据校验*/
    if (depth_frame == NULL)
    {
        return;
    }
    //TODO:进行深度计数据解析
    else if (depth_frame[0] == 0x01 && depth_frame[1] == 0x03 &&  depth_frame[2] == 0x04 && verify_CRC16_check_sum((uint8_t *)depth_frame, 9))
    {
      if(!is_calibrated) // 深度前5次读取的气压值求平均作为大气压参考值
      {
        //深度计发上来的为大端存储
        sum += Byte_to_Float((uint8_t *)&depth_frame[3], true);
        i--;
        if (i == 0)
        {
          is_calibrated = true;
          atmosphere = sum/5.0f;
        }
      }
      else
      {
        pressure1 = Byte_to_Float((uint8_t *)&depth_frame[3], true);
        depth_data = (pressure1 - atmosphere) * 100000.0f / (g * WATER_DENSITY);
      }
    }
}


/**
 * @brief          深度计校准，采集大气压
 * @param[in]      none
 * @return  	   none
*/
void KELLER::calibrate(void)
{
    is_calibrated = false;
}

/**
 * @brief          深度计协议解析，采用状态机方式解析modbus，比较规范
 * @param[in]      none
 * @return  	   none
*/
void KELLER::depth_data_solve(void)
{
  
}

/**
 * @brief          读取深度计寄存器
 * @param[in]      StAdd: 寄存器地址
 * @param[in]      len: 需要读取的寄存器个数
 * @return  	   none
*/
void KELLER::read_register(uint16_t StAdd, uint8_t reg_len)
{
    uint8_t byte_len = reg_len * 2; //一个寄存器两个字节
    depth_tx_buf[0] = this->dev_addr_;
    depth_tx_buf[1] = Register_Read;
    depth_tx_buf[2] = StAdd >> 8;
    depth_tx_buf[3] = StAdd & 0xFF;
    depth_tx_buf[4] = byte_len >> 8;
    depth_tx_buf[5] = byte_len & 0xFF;
    append_CRC16_check_sum(depth_tx_buf, 8);
    SerialPtr_->write(depth_tx_buf, sizeof(depth_tx_buf));

}

/**
 * @brief          写入深度计单个寄存器
 * @param[in]      StAdd: 寄存器地址
 * @param[in]      data: 数据
*/
void KELLER::write_single_register(uint16_t StAdd, uint16_t data)
{
    depth_tx_buf[0] = this->dev_addr_;
    depth_tx_buf[1] = Single_Register_Write;
    depth_tx_buf[2] = StAdd >> 8;
    depth_tx_buf[3] = StAdd & 0xFF;
    depth_tx_buf[4] = data >> 8;
    depth_tx_buf[5] = data & 0xFF;
    append_CRC16_check_sum(depth_tx_buf, 8);
    SerialPtr_->write(depth_tx_buf, sizeof(depth_tx_buf));
}

/**
 * @brief          请求读取一次压力值
 * @param[in]      none
 * @return  	   none
*/
void KELLER::request_data(void)
{
  //读取P1传感器的压力值，P2实测有问题，所以未作处理
  read_register(P1, 1);
}

/**
 * @brief          MS5837构造函数
 * @param[in]      none
 * @return  	     none
*/
MS5837::MS5837(serial::Serial* serialPtr)
{
    configASSERT(serialPtr != nullptr);
    this->SerialPtr_ = serialPtr;
}

/**
 * @brief          MS5837软件复位
 * @param[in]      none
 * @return  	     none
*/
void MS5837::Reset()
{
    uint8_t tx_len = sprintf((char *)depth_tx_buf, "!R\r\n");
    this->SerialPtr_->write(depth_tx_buf, tx_len);
}

/**
 * @brief          深度计协议解析，直接读取压力值
 * @param[in]      depth_frame:原生数据指针
 * @return  	     none
*/
void MS5837::depth_data_solve(volatile const uint8_t *depth_frame)
{
    uint8_t *depth_frame_temp = (uint8_t *)depth_frame;
    for(int i = 0; i < DEPTH_DATA_LENGTH; i++)
    {
        if(*(depth_frame_temp + i) == 'D')
        {
            this->depth_data = atof((char const *)(depth_frame_temp + i + 2));
            break;
        }
    }
}

