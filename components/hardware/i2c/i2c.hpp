#ifndef _I2C_HPP_
#define _I2C_HPP_

#include <vector>
#include "common.hpp"

#ifdef __cplusplus 
extern "C" {
#endif
#include "i2c.h"
#ifdef __cplusplus
}
#endif


enum I2C_FLAG
{
  MASTER = 0x01, //主机
  SLAVE = 0x02, //从机
};

class I2c
{
public:
    I2c(I2C_HandleTypeDef* hi2c, uint32_t Timeout = 100);
    virtual ~I2c();
    void open(I2C_FLAG mode_ = MASTER);
    void close();
    bool isOpen() const
    {
      return isOpen_;
    }
    bool writeto(uint16_t DevAddress, uint8_t* pData, uint16_t Size);
    bool readfrom(uint16_t DevAddress, uint8_t* pData, uint16_t Size);
    bool writeto_mem(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pData, uint16_t Size, uint16_t memAddressSize = I2C_MEMADD_SIZE_8BIT);
    bool readfrom_mem(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pData, uint16_t Size, uint16_t memAddressSize = I2C_MEMADD_SIZE_8BIT);

    std::vector<uint8_t> scan();

      /*! Sets the timeout for reads
      *
      * \param timeout_ms The timeout value in milliseconds
      *
      */
    void
    setTimeout (uint32_t timeout);
    /*! Gets the timeout for reads
      *
      * \return timeout_ms The timeout value in milliseconds
      *
      */
    uint32_t
    getTimeout () const;

private:
    I2C_HandleTypeDef* hi2cPtr_;
    bool isOpen_ = false;
    I2C_FLAG mode_;
    uint32_t timeout_;
};



#endif /* _I2C_HPP_ */
