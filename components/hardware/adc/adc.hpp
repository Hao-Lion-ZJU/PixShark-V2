#ifndef _ADC_HPP_
#define _ADC_HPP_

#include "common.hpp"

#define ADC_VDDA               3.3f
#define FULL_SCALE             65535U

#ifdef __cplusplus 
extern "C" {
#endif
#include "adc.h"
#ifdef __cplusplus
}
#endif

class Adc
{
public:
    Adc(ADC_HandleTypeDef* hadc);
    virtual ~Adc();
    /**
     * @brief  start adc ,if ContinuousConvMode is enable, it will convert again and again
    */
    void start();
    void stop();

    bool isStart() const
    {
        return isStart_;
    }
    /**
     * @brief  read adc value
     * @param  channel: adc channel, the order is assigned by cubemx.
     * @retval adc value
    */
    uint32_t read(uint32_t channel);

    static float get_cpu_temprate(uint32_t raw_value);
    /**
     * @brief  get real vdda value
     *         VDDA = 3.3V*VREFINT_CAL/VREFINT_DATA
     * @param  raw_value: vrefint raw value
     * @retval none
    */
    static float get_real_vdda(uint32_t raw_value);
private:

    ADC_HandleTypeDef* hadcPtr_;
    uint32_t* adc_value;        //convert value buffer, order will be assigned by cubemx.if hadcPtr is hadc3, 0 is vrefint, 1 is temp
    uint32_t channel_num_;
    bool isStart_ = false;
};



#endif /* _ADC_HPP_ */
