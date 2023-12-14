/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : fifo.hpp
 * @brief     : fifo字节环形队列
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
#ifndef _FIFO_HPP_
#define _FIFO_HPP_

#include "common.hpp"

#if USE_OS
//环形字符队列
class fifo_single
{
public:
    fifo_single(uint32_t uint_cnt);
    ~fifo_single();

    bool IsEmpty()
    {
        return (this->used_num ? false : true);
    }
    bool IsFull()
    {
        return (this->free_num ? false : true);
    }

    int fifo_s_used() const
    {
        return used_num;
    }

    int fifo_s_free() const
    {
        return free_num;
    }
    
    int fifo_s_puts(uint8_t* p_source, uint16_t len, bool overwrite = false);


    int fifo_s_gets(uint8_t *p_dest, uint16_t len);

    void fifo_s_flush();

private:
    osMutexId fifo_mutexHandle;      //!< FIFO lock
    uint8_t *p_start_addr; //!< FIFO Memory Pool Start Address
    uint8_t *p_end_addr;   //!< FIFO Memory Pool End Address
    uint32_t free_num;       //!< The remain capacity of FIFO
    uint32_t used_num;       //!< The number of elements in FIFO
    uint8_t unit_size;      //!< FIFO Element Size(Unit: Byte)
    uint8_t *p_read_addr;  //!< FIFO Data Read Index Pointer
    uint8_t *p_write_addr; //!< FIFO Data Write Index Pointer
};

#endif /* USE_OS */

#endif /* _FIFO_HPP_ */