/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : spi.cpp
 * @brief     : spi驱动文件
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


#include "spi/spi.hpp"


Spi::Spi(SPI_HandleTypeDef* hspi, uint32_t Timeout)
{
    configASSERT(hspi != nullptr);
    hspiPtr_ = hspi;
    timeout_ = Timeout;
}


Spi::~Spi()
{
    close();
}


void Spi::open()
{
    if(isOpen_)
    {
        return;
    }
    isOpen_ = true;
}

void Spi::close()
{
    if(isOpen_)
        isOpen_ = false;
}

bool Spi::send(uint8_t* pData, uint16_t Size)
{
    uint8_t hal_result = -1;
    if(isOpen_)
    {
        hal_result = HAL_SPI_Transmit(this->hspiPtr_, pData, Size, timeout_);
        if(hal_result == HAL_OK)
            return true;
        else
            return false;
    }
    else
        return false;
}

bool Spi::recv(uint8_t* pData, uint16_t Size)
{
    uint8_t hal_result = -1;
    if(isOpen_)
    {
        hal_result = HAL_SPI_Receive(this->hspiPtr_, pData, Size, timeout_);
        if(hal_result == HAL_OK)
            return true;
        else
            return false;
    }
    else
        return false;
}

bool Spi::send_recv(uint8_t* pTxData, uint8_t* pRxData, uint16_t Size)
{
    uint8_t hal_result = -1;
    if(isOpen_)
    {
        hal_result = HAL_SPI_TransmitReceive(this->hspiPtr_, pTxData, pRxData, Size, timeout_);
        if(hal_result == HAL_OK)
            return true;
        else
            return false;
    }
    else
        return false;
}


void Spi::setTimeout (uint32_t timeout)
{
    timeout_ = timeout;
}


uint32_t Spi::getTimeout () const
{
    return timeout_;
}