/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : adc.cpp
 * @brief     : DMA方式采集ADC数据
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2022-12-18       Hao Lion        1. <note>
 *  V1.1.0    2023-10-30       Hao Lion        1. 修改为DMA方式读取
 *******************************************************************************
 * @verbatim :
 *==============================================================================
 * 由于ADC采集外部电压存在波动，首先需要借助内部参考电压VREFINT进行校准
 * 根据《STM32H743数据手册》, VDDA = 3.3V*VREFINT_CAL/VREFINT_DATA
 * VREFINT_CAL为芯片出厂时的内部参考电压值，存放在(0x1FF1E860)
 * VREFINT_DATA为ADC采集到的内部参考电压值                                                                  
 *                                                                              
 *==============================================================================
 * @endverbatim :
 *****************************Copyright (c) 2023  ZJU****************************
 */

#include "adc/adc.hpp"


volatile uint16_t VREFINT_CAL; 

Adc::Adc(ADC_HandleTypeDef* hadc)
{
    configASSERT(hadc != nullptr);
    hadcPtr_ = hadc;
    channel_num_ = hadcPtr_->Init.NbrOfConversion;
    adc_value = (uint32_t*)pvPortMalloc(channel_num_ * sizeof(uint32_t));
}

Adc::~Adc()
{
    stop();
    vPortFree(adc_value);
}

void Adc::start()
{
    if(!isStart_)
    {
        HAL_ADCEx_Calibration_Start(hadcPtr_,ADC_CALIB_OFFSET,ADC_SINGLE_ENDED);
        if(hadcPtr_->State == HAL_ADC_STATE_READY)
        {
            HAL_ADC_Start_DMA(hadcPtr_,adc_value,3);
        }
        isStart_ = true;
    }
    
}

void Adc::stop()
{
    if (isStart_)
    {
        HAL_ADC_Stop_DMA(hadcPtr_);
        isStart_ = false;
    }
}

uint32_t Adc::read(uint32_t channel)
{
    configASSERT(channel < 3);
    //清除Cache缓存
	SCB_InvalidateDCache_by_Addr ((uint32_t *)adc_value, channel_num_*sizeof(uint32_t));
    return adc_value[channel];              //convert value buffer, order will be assigned by cubemx.if hadcPtr is hadc3, 0 is vrefint, 1 is temp
}



float Adc::get_real_vdda(uint32_t raw_value)
{
    float voltage_vdda_real = 0;
    voltage_vdda_real = ADC_VDDA*VREFINT_CAL/raw_value;
    return voltage_vdda_real;
    
}




float Adc::get_cpu_temprate(uint32_t raw_value)
{
        float temperate;
        uint16_t TS_CAL1;
        uint16_t TS_CAL2;
        TS_CAL1 = *(__IO uint16_t *)(0x1FF1E820);
        TS_CAL2 = *(__IO uint16_t *)(0x1FF1E840);
        temperate = ((110.0f - 30.0f) / (TS_CAL2 - TS_CAL1)) * (raw_value - TS_CAL1) + 30.0f;
        return temperate;
}