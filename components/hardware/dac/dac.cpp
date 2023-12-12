/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : dac.cpp
 * @brief     : dac驱动文件
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-11-30       Hao Lion        1. <note>
 *******************************************************************************
 * @verbatim :
 *==============================================================================
 *                                                                              
 *                                                                              
 *==============================================================================
 * @endverbatim :
 *****************************Copyright (c) 2023  ZJU****************************
 */

#include "dac/dac.hpp"

Dac::Dac(DAC_HandleTypeDef* hdac)
{
    configASSERT(hdac != nullptr);
    hdacPtr_ = hdac;
}

Dac::~Dac()
{
    stop();
}

void Dac::start()
{
    if(!isStart_)
    {
        HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1,&dac_ch1_value,1,DAC_ALIGN_12B_R);
        HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_2,&dac_ch2_value,1,DAC_ALIGN_12B_R);
        isStart_ = true;
    }
    
}

void Dac::stop()
{
    if(isStart_)
    {
        HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_1);
        HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_2);
        isStart_ = false;
    }
}

void Dac::setvalue(uint32_t channel, uint32_t value)
{
    if(channel == DAC_CHANNEL_1)
    {
        dac_ch1_value = value;
    }
    else if(channel == DAC_CHANNEL_2)
    {
        dac_ch2_value = value;
    }
    else
    {
        configASSERT(0);
    }
}