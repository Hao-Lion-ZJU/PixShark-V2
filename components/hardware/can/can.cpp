/** 
 *****************************Copyright (c) 2023  ZJU****************************
 * @file      : can.cpp
 * @brief     : can驱动文件
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0.0    2023-11-27       Hao Lion        1. <note>
 *******************************************************************************
 * @verbatim :
 *==============================================================================
 *                                                                              
 *                                                                              
 *==============================================================================
 * @endverbatim :
 *****************************Copyright (c) 2023  ZJU****************************
 */


#include "can/can.hpp"
osSemaphoreId* can_semPtr = nullptr;

Can::Can(FDCAN_HandleTypeDef* hcan, uint32_t timeout)
{
    configASSERT(hcan != nullptr);
    hcanPtr_ = hcan;
    timeout_ = timeout;
}

Can::~Can()
{
    stop();
}

void Can::start()
{
    if(isOpen_ || can_semPtr != nullptr)
    {
        return;
    }
    //create semaphore
    osSemaphoreDef(can_sem);
    can_semHandle = osSemaphoreNew(1,0,osSemaphore(can_sem));
    can_semPtr = &can_semHandle;
    if(HAL_FDCAN_Start(hcanPtr_) == HAL_OK)
    {
        isOpen_ = true;
    }
    //set fifo overwrite
    SET_BIT(hcanPtr_->Instance->RXF0C, FDCAN_RXF0C_F0OM);
    //enable interrupt
    if(HAL_FDCAN_ActivateNotification(hcanPtr_,FDCAN_IT_RX_FIFO0_NEW_MESSAGE,0) != HAL_OK)
    {
        Error_Handler();
    }
    if(HAL_FDCAN_ActivateNotification(hcanPtr_,FDCAN_IT_RX_FIFO0_FULL,0) != HAL_OK)
    {
        Error_Handler();
    }
    
}

void Can::stop()
{
    if(!isOpen_)
    {
        return;
    }
    //disable interrupt
    if(HAL_FDCAN_DeactivateNotification(hcanPtr_,FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != HAL_OK)
    {
        Error_Handler();
    }
    if(HAL_FDCAN_DeactivateNotification(hcanPtr_,FDCAN_IT_RX_FIFO0_FULL) != HAL_OK)
    {
        Error_Handler();
    }
    if(HAL_FDCAN_Stop(hcanPtr_) == HAL_OK)
    {
        isOpen_ = false;
    }
}


void Can::setfilter(uint32_t Idtype, uint32_t filter_index, uint32_t Gate, uint32_t Mask)
{
    FDCAN_FilterTypeDef sFilterConfig;
    sFilterConfig.IdType = Idtype;
    sFilterConfig.FilterIndex = filter_index;
    sFilterConfig.FilterType = FDCAN_FILTER_MASK;
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    sFilterConfig.FilterID1 = Gate;
    sFilterConfig.FilterID2 = Mask;
    if(HAL_FDCAN_ConfigFilter(hcanPtr_, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_FDCAN_ConfigGlobalFilter(hcanPtr_, FDCAN_REJECT, FDCAN_REJECT, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE); 
}


bool Can::sendto(uint32_t Id, uint8_t* pData, uint32_t Size, uint32_t Id_type)
{
    configASSERT(Size <= 8);
    FDCAN_TxHeaderTypeDef TxHeader;
    TxHeader.Identifier = Id;											//ID	
    TxHeader.IdType = Id_type;									        //ID类型
    TxHeader.TxFrameType = FDCAN_DATA_FRAME;							//数据帧
    TxHeader.DataLength = (uint32_t)(Size << 16);						//数据长度
	TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	TxHeader.BitRateSwitch = FDCAN_BRS_OFF;								//关闭数据波特率切换
	TxHeader.FDFormat=FDCAN_CLASSIC_CAN;                				//传统的CAN模式
    TxHeader.TxEventFifoControl=FDCAN_NO_TX_EVENTS;     				//无发送事件
    TxHeader.MessageMarker=0;

    uint32_t tickstart;
    /* Init tickstart for timeout management */
    tickstart = HAL_GetTick();
    while(HAL_FDCAN_AddMessageToTxFifoQ(hcanPtr_, &TxHeader, pData) != HAL_OK)
    {
        if (((HAL_GetTick() - tickstart) > timeout_) || (timeout_ == 0U))
        {
            return false;
        }
    }
    return true;
}



int Can::recvfrom(uint32_t& Id, uint32_t& Id_type, uint8_t* pData)
{
    osSemaphoreAcquire(*can_semPtr, timeout_);
    FDCAN_RxHeaderTypeDef RxHeader;
    if(HAL_FDCAN_GetRxMessage(hcanPtr_, FDCAN_RX_FIFO0, &RxHeader, pData) == HAL_OK)
    {
        Id = RxHeader.Identifier;
        Id_type = RxHeader.IdType;
        uint8_t rx_len = RxHeader.DataLength>>16;
        return rx_len;
    }
    else
    {
        return 0;
    }
}


void Can::setTimeout(uint32_t Timeout)
{
    timeout_ = Timeout;
}

uint32_t Can::getTimeout()const
{
    return timeout_;
}


/**
  * @brief          hal库CAN回调函数,接收电机数据
  * @param[in]      hcan:CAN句柄指针
  * @retval         none
  */
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    uint8_t can_id;
    uint8_t rx_data[8];
    FDCAN_RxHeaderTypeDef  rx_header;
	if((RxFifo0ITs&FDCAN_IT_RX_FIFO0_NEW_MESSAGE)!= RESET)
	{
        if (can_semPtr != nullptr)
        {
            osSemaphoreRelease(*can_semPtr);
        }
	}
    else if(RxFifo0ITs&FDCAN_IT_RX_FIFO0_FULL!= RESET)
    {
        //when fifo is full, must put message
        HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rx_header, rx_data);
    }
}
