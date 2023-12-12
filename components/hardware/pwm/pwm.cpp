/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : pwm.cpp
 * @brief     : pwm驱动文件
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-11-25       Hao Lion        1. <note>
 *******************************************************************************
 * @verbatim :
 *==============================================================================
 *                                                                              
 *                                                                              
 *==============================================================================
 * @endverbatim :
 *****************************Copyright (c) 2023  ZJU****************************
 */


#include "pwm/pwm.hpp"

#define TIM_CLOCKS 200000000

Pwm::Pwm(TIM_HandleTypeDef* htim)
{
    configASSERT(htim != nullptr);
    htimPtr_ = htim;
    //start timer
    HAL_TIM_Base_Start(htimPtr_);
    //get auto reload value
    auto_reload_ =  __HAL_TIM_GET_AUTORELOAD(htimPtr_);
}

Pwm::~Pwm()
{
    //stop timer
    HAL_TIM_Base_Stop(htimPtr_);
}

void Pwm::enable(uint32_t channel, uint16_t frequency, uint8_t duty)
{
    if(isEnable_)
    {
        return;
    }
    
    channel_ = channel;
    setFrequency(frequency);
    setDutyCycle(duty);
    //start pwm
    if(HAL_TIM_PWM_Start(htimPtr_, channel_) == HAL_OK)
    {
        isEnable_ = true;
    } 
}

void Pwm::stop()
{
    if(!isEnable_)
    {
        return;
    }
    //stop pwm
    if(HAL_TIM_PWM_Stop(htimPtr_, channel_) == HAL_OK)
    {
        isEnable_ = false;
    }
}

void Pwm::setDutyCycle(uint8_t duty)
{
    if(duty > 100)
    {
        duty = 100;
    }
    else if(duty < 0)
    {
        duty = 0;
    }
    //set duty
    duty_ = duty;
    __HAL_TIM_SET_COMPARE(htimPtr_, channel_, (uint32_t)(duty_ / 100.0f * auto_reload_)); 
}

void Pwm::setFrequency(uint16_t frequency)
{
    uint16_t max_frequency = TIM_CLOCKS / (auto_reload_+1);
    if(frequency > max_frequency)
    {
        frequency = max_frequency;
    }
    else if(frequency < 1)
    {
        frequency = 1;
    }
    //set frequency
    frequency_ = frequency;
    __HAL_TIM_SET_AUTORELOAD(htimPtr_, (uint32_t)(max_frequency/frequency_)-1); 
}   

void Pwm::getFrequency(uint32_t& frequency) const
{
    frequency = frequency_;
}

void Pwm::getDutyCycle(uint8_t& duty) const
{
    duty = duty_;
}


