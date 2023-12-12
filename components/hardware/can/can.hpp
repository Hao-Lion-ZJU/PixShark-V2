#ifndef _CAN_HPP_
#define _CAN_HPP_

#include "common.hpp"

#ifdef __cplusplus 
extern "C" {
#endif
#include "fdcan.h"
#ifdef __cplusplus
}
#endif




class Can
{
public:
    Can(FDCAN_HandleTypeDef* hcan, uint32_t Timeout = 100);
    virtual ~Can();

    void start();
    void stop();

    bool isStart()const
    {
        return isOpen_;
    }

    void setfilter(uint32_t Idtype, uint32_t filter_index, uint32_t Gate, uint32_t Mask);
    bool sendto(uint32_t Id, uint8_t* pData, uint32_t Size, uint32_t Id_type = FDCAN_STANDARD_ID);
    int recvfrom(uint32_t& Id, uint32_t& Id_type, uint8_t* pData);
    
    void setTimeout(uint32_t Timeout);
    uint32_t getTimeout()const;
private:
    FDCAN_HandleTypeDef* hcanPtr_;
    bool isOpen_ = false;
    uint32_t timeout_;
    osSemaphoreId can_semHandle; 
    
};


#endif /* _CAN_HPP_ */
