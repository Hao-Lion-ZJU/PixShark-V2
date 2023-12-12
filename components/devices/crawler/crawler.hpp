#ifndef _CRAWLER_HPP_
#define _CRAWLER_HPP_

#include "common.hpp"
#include "can/can.hpp"

/* ----------------------- Data Struct ------------------------------------- */
#pragma pack(push, 1)


#pragma pack(pop)
/* ----------------------- extern Function ----------------------------------- */


class Crawler
{
public:
    Crawler(/* args */)
    {

    }
    virtual ~Crawler(){};
    virtual void set_expect_speed(int16_t speed_set) = 0;
    virtual int16_t get_rpm() = 0;

protected:
   
    

};

/**
 * @brief   多功能ROV履带的电机，can通讯
*/
class GIANT: public Crawler
{
public:
    GIANT(Can* canPtr,uint32_t _id);//
    ~GIANT(){};

    /**
	 * @brief          初始化硬件
	 * @param[in]      none
	 * @return  	   none
	*/
	void Init()
	{
		if(!canPtr_->isStart())
		{
			canPtr_->start();	
		}
	}

    void set_expect_speed(int16_t speed_set);

    void request_data();

    int16_t get_rpm()
    {
        return crawler_status_msg_.Speed;
    }

    void set_status( int16_t current_feedback, int16_t speed_feedback, int32_t position_feedback)
    {
        this->crawler_status_msg_.Current = current_feedback;
        this->crawler_status_msg_.Speed = speed_feedback;
        this->crawler_status_msg_.Position = position_feedback;
    }
    
private:
    uint32_t CAN_ID;

    Can* canPtr_;

    struct {
        int16_t Current;
        int16_t Speed;
        int32_t Position;
    } crawler_status_msg_;  //回传履带电机状态

    static constexpr auto POSITION_MODE = 0x1E; //设置电机位置模式并下发位置
	static constexpr auto SPEED_MODE = 0x1D; //设置电机速度模式并下发速度
	static constexpr auto GET_CURRENT_SPEED_POSITION = 0x41; //获取当前电流、速度以及位置
	static constexpr auto SAVE_SET = 0X0E; //保存参数设置
    static constexpr auto SET_SPEED_LOOP_P = 0x29; //设置速度环比例
    static constexpr auto SET_SPEED_LOOP_I = 0x2A; //设置速度环积分
    static constexpr auto SET_POSITION_LOOP_P = 0x2B; //设置位置环比例
    static constexpr auto SET_POSITION_LOOP_D = 0x2D; //设置位置环微分
	static constexpr auto SET_BAUD = 0X3F; //设置波特率
	static constexpr auto SED_CAN_ID = 0x2E; // 设置电机id

};



#endif /* _CRAWLER_HPP_ */
