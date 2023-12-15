/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : pwm.cpp
 * @brief     : pwm驱动文件
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-11-25       Hao Lion        1. <note>
 *  V1.0.1    2023-12-15       Qiqi Li         1. fix some bugs
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

Pwm::Pwm(TIM_HandleTypeDef* htim, uint32_t channel)
{
    configASSERT(htim != nullptr);
    this->htimPtr_ = htim;
    this->channel_ = channel;
    //start timer
    HAL_TIM_Base_Start(htimPtr_);
    //get auto reload value
    this->auto_reload_ =  __HAL_TIM_GET_AUTORELOAD(this->htimPtr_);
}

Pwm::~Pwm()
{
    //stop timer
    HAL_TIM_Base_Stop(this->htimPtr_);
}

void Pwm::enable(uint16_t frequency, uint8_t duty)
{
    if(this->isEnable_)
    {
        return;
    }
    
    setFrequency(frequency);
    setDutyCycle(duty);
    //start pwm
    if(HAL_TIM_PWM_Start(this->htimPtr_, this->channel_) == HAL_OK)
    {
        this->isEnable_ = true;
    } 
}

void Pwm::stop()
{
    if(!this->isEnable_)
    {
        return;
    }
    //stop pwm
    if(HAL_TIM_PWM_Stop(this->htimPtr_, this->channel_) == HAL_OK)
    {
        this->isEnable_ = false;
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
    this->duty_ = duty;
    __HAL_TIM_SET_COMPARE(this->htimPtr_, this->channel_, (uint32_t)(this->duty_ / 100.0f * this->auto_reload_)); 
}

void Pwm::setFrequency(uint32_t frequency)
{
    if(frequency > TIM_CLOCKS)
    {
        frequency = TIM_CLOCKS;
    }
    else if(frequency < 1)
    {
        frequency = 1;
    }
    //set frequency
    this->frequency_ = frequency;
    __HAL_TIM_SET_AUTORELOAD(this->htimPtr_,(uint32_t)(TIM_CLOCKS/(frequency_ * this->htimPtr_->Instance->PSC) - 1)); 
}   

void Pwm::getFrequency(uint32_t& frequency) const
{
    frequency = frequency_;
}

void Pwm::getDutyCycle(uint8_t& duty) const
{
    duty = duty_;
}