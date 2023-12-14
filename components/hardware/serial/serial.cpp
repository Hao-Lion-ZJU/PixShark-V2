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
#include "semphr.h"

#define UART_FIFO_SIZE  512 //serial fifo size

#define RS485EN_TX(GPIOx, Pin) {GPIOx->BSRR=Pin;}                         //Pull the level high
#define RS485EN_RX(GPIOx, Pin) {GPIOx->BSRR=(uint32_t)Pin << 16;}          //Pull the level low

typedef struct 
{
    fifo_single* fifo_ptr;
    GPIO_TypeDef* Gpiox;
    uint16_t Pin;
    // osSemaphoreId* semHandlePtr;
    SemaphoreHandle_t uart_sem;
}serial_config_t;


static serial_config_t serial_config[8];


#define get_index(huartptr, index) \
if(huartptr->Instance == USART1) \
index = 0; \
else if(huartptr->Instance == USART2) \
index = 1; \
else if(huartptr->Instance == USART3) \
index = 2; \
else if(huartptr->Instance == UART4) \
index = 3; \
else if(huartptr->Instance == UART5) \
index = 4; \
else if(huartptr->Instance == USART6) \
index = 5; \
else if(huartptr->Instance == UART7) \
index = 6; \
else if(huartptr->Instance == UART8) \
index = 7; 


namespace serial
{
    Serial::Serial(UART_HandleTypeDef* huart,flowcontrol_t flowcontrol, GPIO_TypeDef* GPIOx, uint16_t Pin, uint32_t Timeout)
    {
        configASSERT(huart != nullptr);
        huartPtr_ = huart;
        Timeout_ = Timeout;
        flowcontrol_ = flowcontrol;
        GPIOx_ = GPIOx;
        Pin_ = Pin;
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
            uint8_t index = 0;
            get_index(huartPtr_, index);
            if(serial_config[index].fifo_ptr != nullptr){
                delete uart_fifoPtr_;
                vPortFree(rx_buffer_);
                isOpen_ = false;
            }    
            else{
                serial_config[index].fifo_ptr = uart_fifoPtr_;
                // osSemaphoreDef(sem);
                // semHandle_ = osSemaphoreNew(1,0,osSemaphore(sem));
                // serial_config[index].semHandlePtr = &semHandle_;
                serial_config[index].uart_sem = xSemaphoreCreateBinary();
                semHandle_ = serial_config[index].uart_sem;
                if(flowcontrol_ == flowcontrol_software){
                    configASSERT(GPIOx_ != nullptr);
                    serial_config[index].Gpiox = GPIOx_;
                    serial_config[index].Pin = Pin_;
                }
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

                uint8_t index = 0;
                get_index(huartPtr_, index);
                serial_config[index].fifo_ptr = nullptr;
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
                if(uart_fifoPtr_->IsEmpty())
                {
                    osSemaphoreAcquire(semHandle_, Timeout_);
                }
                read_len = uart_fifoPtr_->fifo_s_gets(buf, len);
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
            if(flowcontrol_ == flowcontrol_software && GPIOx_ != nullptr){
                RS485EN_TX(GPIOx_, Pin_);
            }
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

    uint8_t index = 0;
    get_index(huart, index);
    if(serial_config[index].fifo_ptr != nullptr)
    {
        serial_config[index].fifo_ptr->fifo_s_puts(rx_buffer, Size, true);
        osSemaphoreRelease((osSemaphoreId_t)(serial_config[index].uart_sem));
    }      

    //重新开启DMA接收
    HAL_UARTEx_ReceiveToIdle_DMA(huart, rx_buffer, UART_FIFO_SIZE);
}

/**
  * @brief Tx Transfer completed callback.
  * @param huart UART handle.
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    uint8_t index = 0;
    get_index(huart, index);
    if(serial_config[index].Gpiox != nullptr)
    {
        RS485EN_RX(serial_config[index].Gpiox, serial_config[index].Pin);
    }
}