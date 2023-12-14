#include "timer/timer.hpp"

static TimerCallback_t timerCallbacks[13];

Timer::Timer(TIM_HandleTypeDef * htim, timerMode mode)
{
    configASSERT(htim != nullptr);
    this->htim_ = htim;
    this->mode_ = mode;
}

void Timer::start()
{
    if(mode_ == Polling)
    {
        HAL_TIM_Base_Start(htim_);
    }
    else if(mode_ == Interrupt)
    {
        HAL_TIM_Base_Start_IT(htim_);
    }
    this->isStart_ = true;
}

void Timer::stop()
{
    if(mode_ == Polling)
    {
        HAL_TIM_Base_Stop(htim_);
    }
    else if(mode_ == Interrupt)
    {
        HAL_TIM_Base_Stop_IT(htim_);
    }
    this->isStart_ = false;
}

uint16_t Timer::get_count()
{
    uint16_t count = __HAL_TIM_GET_COUNTER(htim_);
    __HAL_TIM_SET_COUNTER(&htim3, 0);
    return count;
}

void Timer::SetCallback(TimerCallback_t timerCallback)
{
    if(htim_->Instance == TIM2)
    {
        timerCallbacks[0] = timerCallback;
    }
    else if(htim_->Instance == TIM3)
    {
        timerCallbacks[1] = timerCallback;
    }
    else if(htim_->Instance == TIM4)
    {
        timerCallbacks[2] = timerCallback;
    }
    else if(htim_->Instance == TIM5)
    {
        timerCallbacks[3] = timerCallback;
    }
    else if(htim_->Instance == TIM6)
    {
        timerCallbacks[4] = timerCallback;
    }
    else if(htim_->Instance == TIM7)
    {
        timerCallbacks[5] = timerCallback;
    }
    else if(htim_->Instance == TIM8)
    {
        timerCallbacks[6] = timerCallback;
    }
    else if(htim_->Instance == TIM12)
    {
        timerCallbacks[7] = timerCallback;
    }
    else if(htim_->Instance == TIM13)
    {
        timerCallbacks[8] = timerCallback;
    }
    else if(htim_->Instance == TIM14)
    {
        timerCallbacks[9] = timerCallback;
    }
    else if(htim_->Instance == TIM15)
    {
        timerCallbacks[10] = timerCallback;
    }
    else if(htim_->Instance == TIM16)
    {
        timerCallbacks[11] = timerCallback;
    }
    else if(htim_->Instance == TIM17)
    {
        timerCallbacks[12] = timerCallback;
    }
}

extern "C"
void OnTimerCallback(TIM_TypeDef *timInstance)
{
    if (timInstance == TIM2)
    {
        timerCallbacks[0]();
    } 
    else if (timInstance == TIM3)
    {
        timerCallbacks[1]();
    } 
    else if (timInstance == TIM4)
    {
        timerCallbacks[2]();
    } 
    else if (timInstance == TIM5)
    {
        timerCallbacks[3]();
    } 
    else if (timInstance == TIM6)
    {
        timerCallbacks[4]();
    }
    else if (timInstance == TIM7)
    {
        timerCallbacks[5]();
    }
    else if (timInstance == TIM8)
    {
        timerCallbacks[6]();
    } 
    else if (timInstance == TIM12)
    {
        timerCallbacks[7]();
    } 
    else if (timInstance == TIM13)
    {
        timerCallbacks[8]();
    } 
    else if (timInstance == TIM14)
    {
        timerCallbacks[9]();
    }
    else if (timInstance == TIM15)
    {
        timerCallbacks[10]();
    }
    else if (timInstance == TIM16)
    {
        timerCallbacks[11]();
    }
    else if (timInstance == TIM17)
    {
        timerCallbacks[12]();
    }       
}

