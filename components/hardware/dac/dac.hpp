#ifndef _DAC_HPP_
#define _DAC_HPP_

#include "common.hpp"

#ifdef __cplusplus 
extern "C" {
#endif
#include "dac.h"
#ifdef __cplusplus
}
#endif


class Dac
{
public:
    Dac(DAC_HandleTypeDef* hdac);
    virtual ~Dac();

    void start();
    void stop();

    bool isStart() const
    {
        return isStart_;
    }

    void setvalue(uint32_t channel, uint32_t value);
private:

    DAC_HandleTypeDef* hdacPtr_;
    uint32_t dac_ch1_value = 0;
    uint32_t dac_ch2_value = 0;
    bool isStart_ = false;
};

#endif /* _DAC_HPP_ */
