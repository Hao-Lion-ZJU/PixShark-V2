/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : serial.cpp
 * @brief     : stm32串口驱动文件, 仅测试过STM32H743平台可用，需要在FreeRTOS下使用
 *              串口接收使用DMA+IDLE中断，存入FIFO内，使得用户可以像在UNIX上面一样读取串口数据
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-10-15       Hao Lion        1. <note>
 *******************************************************************************
 * @verbatim :
 *==============================================================================
 *                                                                              
 *                                                                              
 *==============================================================================
 * @endverbatim :
 *****************************Copyright (c) 2023  ZJU****************************
 */

#include "serial/serial.hpp"
#include <string.h>

#define UART_FIFO_SIZE  512 //串口fifo缓存大小

/**stm32 串口缓存区*/
static fifo_single* fifo_usart1_ptr;
static fifo_single* fifo_usart2_ptr;
static fifo_single* fifo_usart3_ptr;
static fifo_single* fifo_uart4_ptr;
static fifo_single* fifo_uart5_ptr;
static fifo_single* fifo_usart6_ptr;
static fifo_single* fifo_uart7_ptr;
static fifo_single* fifo_uart8_ptr;


namespace serial
{
    Serial::Serial(UART_HandleTypeDef* huart, uint32_t Timeout)
    {
        configASSERT(huart != nullptr);
        huartPtr_ = huart;
        Timeout_ = Timeout;
    }

    Serial::~Serial()
    {
        close(); 
    }

    void Serial::open(UART_FLAG&& mode)
    {   
        if(isOpen_)
        {
            return;
        }

        mode_ = mode;
        isOpen_ = true;
        if(mode == O_WRONLY)
        {
            HAL_UART_AbortReceive_IT(huartPtr_);
        }
        else if(mode == O_RDONLY || mode == O_RDWR)
        {
            uart_fifoPtr_ = new fifo_single(UART_FIFO_SIZE);
            configASSERT(uart_fifoPtr_ != nullptr);
            rx_buffer_ = (uint8_t*)pvPortMalloc(UART_FIFO_SIZE);
            configASSERT(rx_buffer_ != nullptr);
             if(huartPtr_->Instance == USART1)
            {
                //has been opened
                if(fifo_usart1_ptr != nullptr){
                    delete uart_fifoPtr_;
                    vPortFree(rx_buffer_);
                    isOpen_ = false;
                }    
                else{
                    fifo_usart1_ptr = uart_fifoPtr_;
                }
            }
            else if(huartPtr_->Instance == USART2)
            {
                if(fifo_usart2_ptr != nullptr){
                    delete uart_fifoPtr_;
                    vPortFree(rx_buffer_);
                    isOpen_ = false;
                }    
                else{
                    fifo_usart2_ptr = uart_fifoPtr_;
                }
            }
            else if(huartPtr_->Instance == USART3)
            {
                if(fifo_usart3_ptr != nullptr){
                    delete uart_fifoPtr_;
                    vPortFree(rx_buffer_);
                    isOpen_ = false;
                }    
                else{
                    fifo_usart3_ptr = uart_fifoPtr_;
                }
            }
            else if(huartPtr_->Instance == UART4)
            {
                if(fifo_uart4_ptr != nullptr){
                    delete uart_fifoPtr_;
                    vPortFree(rx_buffer_);
                    isOpen_ = false;
                }    
                else{
                    fifo_uart4_ptr = uart_fifoPtr_;
                }
            }
            else if(huartPtr_->Instance == UART5)
            {
                if(fifo_uart5_ptr != nullptr){
                    delete uart_fifoPtr_;
                    vPortFree(rx_buffer_);
                    isOpen_ = false;
                }    
                else{
                    fifo_uart5_ptr = uart_fifoPtr_;
                }
            }
            else if(huartPtr_->Instance == USART6)
            {
                if(fifo_usart6_ptr != nullptr){
                    delete uart_fifoPtr_;
                    vPortFree(rx_buffer_);
                    isOpen_ = false;
                }    
                else{
                    fifo_usart6_ptr = uart_fifoPtr_;
                }
            }
            else if(huartPtr_->Instance == UART7)
            {
                if(fifo_uart7_ptr != nullptr){
                    delete uart_fifoPtr_;
                    vPortFree(rx_buffer_);
                    isOpen_ = false;
                }    
                else{
                    fifo_uart7_ptr = uart_fifoPtr_;
                }
            }
            else if(huartPtr_->Instance == UART8)
            {
                if(fifo_uart8_ptr != nullptr){
                    delete uart_fifoPtr_;
                    vPortFree(rx_buffer_);
                    isOpen_ = false;
                }    
                else{
                    fifo_uart8_ptr = uart_fifoPtr_;
                }
            }
            else
            {
                configASSERT(0);
            }
            HAL_UARTEx_ReceiveToIdle_DMA(huartPtr_, rx_buffer_, UART_FIFO_SIZE);
            if(mode == O_RDONLY)
            {
                HAL_UART_AbortTransmit_IT(huartPtr_);
            }
        }
        else
        {
            configASSERT(0);
        }
    }

    bool Serial::isOpen() const
    {
        return isOpen_;
    }

    void Serial::close()
    {
        if (isOpen_)
        {
            //终止串口的接收和发送
            HAL_UART_AbortTransmit_IT(huartPtr_);
            HAL_UART_AbortReceive_IT(huartPtr_);
            isOpen_ = false;
            if(mode_ == O_RDONLY || mode_ == O_RDWR){
                if(huartPtr_->Instance == USART1)
                {
                    fifo_usart1_ptr = nullptr;
                } else if(huartPtr_->Instance == USART2)
                {
                    fifo_usart2_ptr = nullptr;
                } else if(huartPtr_->Instance == USART3)
                {
                    fifo_usart3_ptr = nullptr;
                } else if(huartPtr_->Instance == UART4)
                {
                    fifo_uart4_ptr = nullptr;
                } else if(huartPtr_->Instance == UART5)
                {
                    fifo_uart5_ptr = nullptr;
                } else if(huartPtr_->Instance == USART6)
                {
                    fifo_usart6_ptr = nullptr;
                } else if(huartPtr_->Instance == UART7)
                {
                    fifo_uart7_ptr = nullptr;
                } else if(huartPtr_->Instance == UART8)
                {
                    fifo_uart8_ptr = nullptr;            
                }
                delete uart_fifoPtr_;
                vPortFree(rx_buffer_);
            }
        }
    }

    size_t Serial::available()
    {
        if (isOpen_)
        {
            return uart_fifoPtr_->fifo_s_used();
        }
        else
        {
            return 0;
        }
    }

    size_t Serial::read(uint8_t* buf, size_t len)
    {
        if((mode_ == O_RDONLY || mode_ == O_RDWR) && isOpen_ && (len > 0))
        {
            size_t read_len = 0;
            if (uart_fifoPtr_ != nullptr)
            {
                read_len = uart_fifoPtr_->fifo_s_gets(buf, len, Timeout_);
            }
            return read_len;
        }
        else
        {
            return -1;
        } 
    }

    size_t Serial::write(const uint8_t* buf, size_t len)
    {
        if((mode_ == O_WRONLY || mode_ == O_RDWR) && isOpen_ && (len > 0))
        {
            HAL_UART_Transmit_DMA(huartPtr_, (uint8_t*)buf, len);
            return len;
        }
        else
        {
            return -1;
        }
    }

    size_t Serial::readline (uint8_t* buffer, size_t size, const char eol)
    {
        if((mode_ == O_RDONLY || mode_ == O_RDWR) && isOpen_){
            size_t read_so_far = 0;
            while (true)
            {
                size_t bytes_read = this->read(buffer + read_so_far, 1);
                read_so_far += bytes_read;
                if (bytes_read == 0) {
                    break; // Timeout occured on reading 1 byte
                }
                if (*(buffer + read_so_far - 1) == eol) {
                break; // EOL found
                }
                if (read_so_far == size) {
                break; // Reached the maximum read length
                }
            }
            return read_so_far;
        }
        else
        {
            return -1;
        }
       
    }

    void Serial::flush()
    {
        uart_fifoPtr_->fifo_s_flush();
    }

    void Serial::setTimeout(uint32_t timeout)
    {
        Timeout_ = timeout;
    }

    uint32_t Serial::getTimeout() const
    {
        return Timeout_;
    }
    

    
} // namespace serial 


/**
  * @brief  Reception Event Callback (Rx event notification called after use of advanced reception service).
  * @param  huart UART handle
  * @param  Size  Number of data available in application reception buffer (indicates a position in
  *               reception buffer until which, data are available)
  * @retval None
  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    uint8_t* rx_buffer = huart->pRxBuffPtr;
    //清除Cache缓存
	SCB_InvalidateDCache_by_Addr ((uint32_t *)rx_buffer, Size);

        if(huart->Instance == USART1)
        {
            if(fifo_usart1_ptr != nullptr)
            {
                fifo_usart1_ptr->fifo_s_puts(rx_buffer, Size, true);
            }
        } else if(huart->Instance == USART2)
        {
            if(fifo_usart2_ptr != nullptr)
            {
                fifo_usart2_ptr->fifo_s_puts(rx_buffer, Size, true);
            }
        } else if(huart->Instance == USART3)
        {
            if(fifo_usart3_ptr != nullptr)
            {
                fifo_usart3_ptr->fifo_s_puts(rx_buffer, Size, true);
            }
        } else if(huart->Instance == UART4)
        {
            if(fifo_uart4_ptr != nullptr)
            {
                fifo_uart4_ptr->fifo_s_puts(rx_buffer, Size, true);
            }
        } else if(huart->Instance == UART5)
        {
            if(fifo_uart5_ptr != nullptr)
            {
                fifo_uart5_ptr->fifo_s_puts(rx_buffer, Size, true);
            }
        } else if(huart->Instance == USART6)
        {
            if(fifo_usart6_ptr != nullptr)
            {
                fifo_usart6_ptr->fifo_s_puts(rx_buffer, Size, true);
            }
        } else if(huart->Instance == UART7)
        {
            if(fifo_uart7_ptr != nullptr)
            {
                fifo_uart7_ptr->fifo_s_puts(rx_buffer, Size, true);
            }
        } else if(huart->Instance == UART8)
        {
            if(fifo_uart8_ptr != nullptr)
            {
                fifo_uart8_ptr->fifo_s_puts(rx_buffer, Size, true);
            }      
        }

    //重新开启DMA接收
    HAL_UARTEx_ReceiveToIdle_DMA(huart, rx_buffer, UART_FIFO_SIZE);
            

}

