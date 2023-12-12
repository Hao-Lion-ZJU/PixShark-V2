#include"crawler/crawler.hpp"

GIANT::GIANT(Can * canPtr, uint32_t id)
{
    configASSERT(canPtr != nullptr);
    this->CAN_ID = id;
    this->canPtr_ = canPtr;
}



void GIANT::set_expect_speed(int16_t speed_set)
{
    int32_t speed_temp = (int32_t)speed_set;
    uint8_t speed_buf[5] = {0};
    uint16_t send_len = 5;
    speed_buf[0] = SPEED_MODE;

    memcpy(&speed_buf[1],&speed_temp,4);

    canPtr_->sendto(this->CAN_ID,speed_buf,send_len);

}

void GIANT::request_data()
{
    uint8_t cmd_buf[1];
    cmd_buf[0] = GET_CURRENT_SPEED_POSITION;
    canPtr_->sendto(this->CAN_ID,cmd_buf,1);
}
