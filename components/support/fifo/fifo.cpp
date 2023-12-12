/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : fifo.cpp
 * @brief     : fifo字节环形队列，用于FreeRTOS
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-5-30       Hao Lion        1. <note>
 *******************************************************************************
 * @verbatim :
 *==============================================================================
 *                                                                              
 *                                                                              
 *==============================================================================
 * @endverbatim :
 *****************************Copyright (c) 2023  ZJU****************************
 */

#include"fifo/fifo.hpp"

#if USE_OS

typedef enum {
    FIFO_OK = 1,		//操作成功
	FIFO_Empty = 0, //队列空
	FIFO_Full = -1,		//队列满
	
}QueueState;

fifo_single::fifo_single(uint32_t uint_cnt)
{
    
    //! Check input parameters.
    configASSERT(uint_cnt > 0);

    //!Define mutex
    osMutexDef(fifo_mutex);
    //! Define semaphore
    osSemaphoreDef(fifo_sem);
    //! Create mutex and semaphore
    #if (osCMSIS < 0x20000U)
    fifo_semHandle = osSemaphoreCreate(osSemaphore(fifo_sem),1);
    fifo_mutexHandle = osMutexCreate(osMutex(fifo_mutex));
    #else
    fifo_semHandle = osSemaphoreNew(1,0,osSemaphore(fifo_sem));
    fifo_mutexHandle = osMutexNew(osMutex(fifo_mutex));
    #endif
    //! Allocate Memory for pointer of new FIFO
    this->p_start_addr = (uint8_t*)pvPortMalloc(uint_cnt);
    //! Allocate Failure, exit now
    configASSERT(p_start_addr!=nullptr);
    //! Initialize FIFO Control Block.
    this->p_end_addr = (uint8_t *)p_start_addr + uint_cnt - 1;
    this->free_num = uint_cnt;
    this->used_num = 0;
    this->p_read_addr = (uint8_t *)p_start_addr;
    this->p_write_addr = (uint8_t *)p_start_addr;
    this->unit_size = 1;
    this->empty_flag = true;
}

fifo_single::~fifo_single()
{
    configASSERT(p_start_addr!=nullptr);
    vPortFree(p_start_addr);
    p_start_addr = nullptr;
}

int fifo_single::fifo_s_gets(uint8_t *p_dest, uint16_t len, uint32_t timeout)
{
    int retval;
    uint16_t len_to_end;
    int len_from_start;


    configASSERT(p_dest);

    if (0 == this->used_num)
    {
        empty_flag = true;
        //规定时间内为获得数据，返回错误
        if(osSemaphoreAcquire(fifo_semHandle, timeout) != osOK){
            return FIFO_Empty;
        }
    }
    //! add lock
    osMutexWait(fifo_mutexHandle, osWaitForever);
    if (this->p_read_addr > this->p_end_addr)
        this->p_read_addr = this->p_start_addr;

    len = (len < this->used_num) ? len : this->used_num;
    len_to_end = this->p_end_addr - this->p_read_addr + 1;

    if (len_to_end >= len) //no rollback
    {
        len_to_end = len;
        memcpy(p_dest, this->p_read_addr, len_to_end);
        this->p_read_addr += len_to_end;
    }
    else //rollback
    {
        len_from_start = len - len_to_end;
        memcpy(p_dest, p_read_addr, len_to_end);
        memcpy(p_dest + len_to_end, this->p_start_addr, len_from_start);
        this->p_read_addr = this->p_start_addr + len_from_start;
    }

    this->free_num += len;
    this->used_num -= len;
    //! release lock
    osMutexRelease(fifo_mutexHandle);
    

    retval = len;
    return retval;
}



int fifo_single::fifo_s_puts(uint8_t* p_source, uint16_t len, bool overwrite)
{
    int retval;
    uint16_t len_to_end;
    uint16_t len_put = len;
    int len_from_start;

    configASSERT(p_source);
    if(empty_flag && len > 0){
        osSemaphoreRelease(fifo_semHandle);
        empty_flag = false;
    }

    if (0 == this->free_num)
    {
        if (!overwrite)
        {
            return FIFO_Full;
        }
        else    //overwrite
        {
            //! add lock
            osMutexWait(fifo_mutexHandle, osWaitForever);
            if (this->p_read_addr > this->p_end_addr)
                this->p_read_addr = this->p_start_addr;

            len_put = (len_put < this->used_num) ? len_put : this->used_num;
            len_to_end = this->p_end_addr - this->p_read_addr + 1;

            if (len_to_end >= len_put) //no rollback
            {
                len_to_end = len_put;
                this->p_read_addr += len_to_end;
            }
            else //rollback
            {
                len_from_start = len_put - len_to_end;
                this->p_read_addr = this->p_start_addr + len_from_start;
            }

            this->free_num += len_put;
            this->used_num -= len_put;
            //! release lock
            osMutexRelease(fifo_mutexHandle);
        }
        
    }
    //! add lock
    osMutexWait(fifo_mutexHandle, osWaitForever);
    if (this->p_write_addr > this->p_end_addr)
    this->p_write_addr = this->p_start_addr;

    len = (len < this->free_num) ? len : this->free_num;
    len_to_end = this->p_end_addr - this->p_write_addr + 1;
    if (len_to_end >= len) //no rollback
    {
        len_to_end = len;
        memcpy(this->p_write_addr, p_source, len_to_end);
        this->p_write_addr += len_to_end;
    }
    else //rollback
    {
        len_from_start = len - len_to_end;
        memcpy(this->p_write_addr, p_source, len_to_end);
        memcpy(this->p_start_addr, p_source + len_to_end, len_from_start);
        this->p_write_addr = this->p_start_addr + len_from_start;
    }

    this->free_num -= len;
    this->used_num += len;
    //! release lock
    osMutexRelease(fifo_mutexHandle);
    
    retval = len;

    
    return retval;
}

void fifo_single::fifo_s_flush()
{
    //! add lock
    osMutexWait(fifo_mutexHandle, osWaitForever);

    this->free_num = this->p_end_addr - this->p_start_addr + 1;
    this->used_num = 0;
    this->p_read_addr = this->p_start_addr;
    this->p_write_addr = this->p_start_addr;

    //! release lock
    osMutexRelease(fifo_mutexHandle);
}

#endif // USE_OS