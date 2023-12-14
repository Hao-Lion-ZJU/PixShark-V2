#ifndef _SERIAL_HPP_
#define _SERIAL_HPP_

#ifdef __cplusplus 
extern "C" {
#endif
#include "usart.h"

#ifdef __cplusplus
}
#endif

#include "fifo/fifo.hpp"



enum UART_FLAG
{
  O_RDONLY = 0x01, //只接受数据
  O_WRONLY = 0x02, //只发送数据
  O_RDWR = 0x03   //收发数据
};

/*!
 * Enumeration defines the possible flowcontrol types for the serial port.
 */
typedef enum {
  flowcontrol_none = 0,
  flowcontrol_software,
  flowcontrol_hardware
} flowcontrol_t;

namespace serial
{

class Serial
{
public:
    /*!
    * Creates a Serial object,
    * it's param will be configed by CubeMx.
    *
    * \param huart  UART handle 
    *
    * \param timeout Timeout before read/write calls return, default is forever
    * 
    * \param flowcontrol Type of flowcontrol used, default is
    * flowcontrol_none, possible values are: flowcontrol_none,
    * flowcontrol_software, flowcontrol_hardware
    *
    */
    Serial (UART_HandleTypeDef* huart,flowcontrol_t flowcontrol = flowcontrol_none, GPIO_TypeDef* GPIOx = nullptr, uint16_t Pin = 0, uint32_t Timeout = 100);

    /*! Destructor */
    virtual ~Serial ();

    /*!
    * Opens the serial port
    * the serial can be opened in one of the following modes:
    * * O_RDONLY: Open port for read only
    * * O_WRONLY: Open port for write only
    * * O_RDWR  : Open port for both reading and writing
    * the same huart handle can be opened many times in O_WRONLY mode 
    *
    * \see Serial::Serial
    *
    */
    void
    open (UART_FLAG&& mode = O_RDWR);

    /*! Gets the open status of the serial port.
    *
    * \return Returns true if the port is open, false otherwise.
    */
    bool
    isOpen () const;

    /*! Closes the serial. */
    void
    close ();

    /*! Return the number of characters in the buffer. */
    size_t
    available ();

    /*! Read a given amount of bytes from the serial port into a given buffer.
    *
    * The read function will return in one of three cases:
    *  * The number of requested bytes was read.
    *    * In this case the number of bytes requested will match the size_t
    *      returned by read.
    *  * Thenumber of bytes read will not match the amount requested, but fifo
    *    isn't empty.
    *    * In this case will return the number of bytes retained in the fifo.
    *  * A timeout occurred,  but the fifo is still empty.
    *    * In this case the number of bytes read will be 0.
    *
    * \param buffer An uint8_t array of at least the requested size.
    * \param size A size_t defining how many bytes to be read.
    *
    * \return A size_t representing the number of bytes read as a result of the
    *         call to read.
    */
    size_t
    read (uint8_t *buffer, size_t size);

    /*! Write a string to the serial port.
    *
    * \param data A const reference containing the data to be written
    * to the serial port.
    *
    * \param size A size_t that indicates how many bytes should be written from
    * the given data buffer.
    *
    * \return A size_t representing the number of bytes actually written to
    * the serial port.
    *
    */
    size_t
    write (const uint8_t *data, size_t size);
    /*! Reads in a line or until a given delimiter has been processed.
    *
    * Reads from the serial port until a single line has been read.
    *
    * \param buffer A std::string reference used to store the data.
    * \param size A maximum length of a line, defaults to 512 (2^8)
    * \param eol A string to match against for the EOL.
    *
    * \return A size_t representing the number of bytes read.
    *
    */
    size_t
    readline (uint8_t* buffer, size_t size = 512, const char eol = '\n');

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

  /*! Flush  the receive buffer */
  void
  flush ();


private:
    UART_HandleTypeDef* huartPtr_;
    fifo_single* uart_fifoPtr_;
    osSemaphoreId semHandle_;
    bool isOpen_ = false;
    uint32_t Timeout_;
    uint8_t* rx_buffer_;
    UART_FLAG mode_;
    uint8_t flowcontrol_;
    GPIO_TypeDef* GPIOx_;
    uint16_t Pin_;
};

} // namespace serial

#endif /* _SERIAL_HPP_ */
