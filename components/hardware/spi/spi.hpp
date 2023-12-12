#ifndef _SPI_HPP_
#define _SPI_HPP_

#ifdef __cplusplus 
extern "C" {
#endif
#include "spi.h"
#ifdef __cplusplus
}
#endif

#include "common.hpp"

enum SPI_FLAG
{
  MASTER = 0x01, //主机
  SLAVE = 0x02, //从机
};

class Spi
{
public:
    Spi(SPI_HandleTypeDef* hspi, uint32_t Timeout = 100);
    virtual ~Spi();
    void open();
    void close();

    bool isOpen() const
    {
      return isOpen_;
    }

    bool send(uint8_t* pData, uint16_t Size);

    bool recv(uint8_t* pData, uint16_t Size);

    bool send_recv(uint8_t* pTxData, uint8_t* pRxData, uint16_t Size);



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
    SPI_HandleTypeDef* hspiPtr_;
    bool isOpen_ = false;
    uint32_t timeout_;
};

#endif /* _SPI_HPP_ */
