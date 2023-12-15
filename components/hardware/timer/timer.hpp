#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include "common.hpp"

#ifdef __cplusplus 
extern "C" {
#endif
#include "tim.h"
#ifdef __cplusplus
}
#endif

enum timerMode
{
    Polling, //Blocking mode
    Interrupt, //Non-Blocking mode
};

typedef void (*TimerCallback_t)();

class Timer
{
public:
    Timer(TIM_HandleTypeDef * htim, timerMode mode);
    virtual ~Timer();

    void SetCallback(TimerCallback_t timerCallback);

    void start();

    void stop();

    uint16_t get_count();

    bool isStart() const
    {
        return isStart_;
    }

private:
    
    TIM_HandleTypeDef *htim_;

    timerMode mode_;
    bool isStart_ = false;
    
};

#endif