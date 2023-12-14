#ifndef _PWM_HPP_
#define _PWM_HPP_

#include "common.hpp"

#ifdef __cplusplus 
extern "C" {
#endif
#include "tim.h"
#ifdef __cplusplus
}
#endif


class Pwm
{
public:
    Pwm(TIM_HandleTypeDef* htim, uint32_t channel);
    virtual ~Pwm();
    void enable(uint16_t frequency, uint8_t duty);
    void stop();
    bool isEnable() const
    {
        return isEnable_;
    }
    void setDutyCycle(uint8_t duty);
    void setFrequency(uint32_t frequency);
    void getFrequency(uint32_t& frequency) const;
    void getDutyCycle(uint8_t& duty) const;

private:
    TIM_HandleTypeDef* htimPtr_;
    bool isEnable_ = false;
    uint32_t channel_;
    uint32_t auto_reload_;
    uint32_t frequency_;
    uint8_t duty_;
};  
#endif /* _PWM_HPP_ */
