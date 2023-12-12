/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : i2c.cpp
 * @brief     : i2c驱动文件
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


#include "i2c/i2c.hpp"


I2c::I2c(I2C_HandleTypeDef* hi2c, uint32_t Timeout)
{
    configASSERT(hi2c != nullptr);
    hi2cPtr_ = hi2c;
    timeout_ = Timeout;
}


I2c::~I2c()
{
    close();
}


void I2c::open(I2C_FLAG mode)
{
    if(isOpen_)
    {
        return;
    }
    this->mode_ = mode;
    isOpen_ = true;
}

void I2c::close()
{
    if(isOpen_)
        isOpen_ = false;
}


bool I2c::writeto(uint16_t DevAddress, uint8_t* pData, uint16_t Size)
{
    uint8_t hal_result = -1;
    if(isOpen_)
    {
        if(mode_ == MASTER)
            hal_result = HAL_I2C_Master_Transmit(this->hi2cPtr_, DevAddress, pData, Size, timeout_);
        else if(mode_ == SLAVE)
            hal_result = HAL_I2C_Slave_Transmit(this->hi2cPtr_, pData, Size, timeout_);
        if(hal_result == HAL_OK)
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}


bool I2c::readfrom(uint16_t DevAddress, uint8_t* pData, uint16_t Size)
{
    uint8_t hal_result = -1;
    if(isOpen_)
    {
        if(mode_ == MASTER)
            hal_result = HAL_I2C_Master_Receive(this->hi2cPtr_, DevAddress, pData, Size, timeout_);
        else if(mode_ == SLAVE)
            hal_result = HAL_I2C_Slave_Receive(this->hi2cPtr_, pData, Size, timeout_);
        if(hal_result == HAL_OK)
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}

bool I2c::writeto_mem(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pData, uint16_t Size, uint16_t memAddressSize)
{
    uint8_t hal_result = -1;
    if(isOpen_)
    {
        //only master can write to mem
        if(mode_ == MASTER)
            hal_result = HAL_I2C_Mem_Write(this->hi2cPtr_, DevAddress, MemAddress, memAddressSize, pData, Size, timeout_);
        if(hal_result == HAL_OK)
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}


bool I2c::readfrom_mem(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pData, uint16_t Size, uint16_t memAddressSize)
{
    uint8_t hal_result = -1;
    if(isOpen_)
    {
        //only master can read from mem
        if(mode_ == MASTER)
            hal_result = HAL_I2C_Mem_Read(this->hi2cPtr_, DevAddress, MemAddress, memAddressSize, pData, Size, timeout_);
        if(hal_result == HAL_OK)
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}


std::vector<uint8_t> I2c::scan()
{
    std::vector<uint8_t> result;
    if(isOpen_)
    {
        for(uint8_t i = 0; i < 128; i++)
        {
            if(HAL_I2C_IsDeviceReady(this->hi2cPtr_, i, 1, timeout_) == HAL_OK)
            {
                result.push_back(i);
            }
        }
    }
    return result;
}

void I2c::setTimeout(uint32_t timeout)
{
    this->timeout_ = timeout;
}

uint32_t I2c::getTimeout() const
{
    return this->timeout_;
}