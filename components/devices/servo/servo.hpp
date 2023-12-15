#ifndef _SERVO_HPP_
#define _SERVO_HPP_


#include "common.hpp"
#include "serial/serial.hpp"
#include "pwm/pwm.hpp"



class Servo
{
public:
    Servo(){};
    virtual ~Servo(){};
    virtual void set_servo_angle(int16_t angle_set) = 0;
    virtual int16_t get_servo_angle() = 0;
private:

};

/**
 * 霸勒斯舵机，485通讯
*/
class AUSServo : public Servo
{
public:
    AUSServo(serial::Serial* SerialPtr  ,uint8_t id);
    ~AUSServo(){};

    /**
	 * @brief          初始化硬件
	 * @param[in]      none
	 * @return  	   none
	*/
	void Init()
	{
		if(!SerialPtr_->isOpen())
		{
			SerialPtr_->open(O_WRONLY);	
		}
	}

    /**
     * @brief 设置舵机控制角度，-180~180为单圈，在-180~180外，函数内部调用set_servo_angle_multi_turn
     * @param[in] angle_set:  舵机角度
     * @retval none
    */
    void set_servo_angle(int16_t angle_set);
    /**
     * @brief 设置舵机控制角度，-180~180为单圈，在-180~180外，函数内部调用set_servo_angle_multi_turn
     * @param[in] angle_set:  舵机角度
     * @param[in] time_ms:    舵机运行时间
     * @retval none
    */
    void set_servo_angle(int16_t angle_set, uint16_t time_ms);
    /**
     * @brief 设置舵机控制角度(多圈)
     * @param[in] angle_set:  舵机角度
     * @retval none
    */
    void set_servo_angle_multi_turn(int angle_set);
    /**
     * @brief 设置舵机控制角度(多圈)
     * @param[in] angle_set:  舵机角度
     * @param[in] time_ms:    舵机运行时间
     * @retval none
    */
    void set_servo_angle_multi_turn(int angle_set, unsigned int time_ms);


    /**
     * @brief 获取舵机角度
     * @retval none
    */
    int16_t get_servo_angle(void);

    /**
     * @brief 修改舵机ID
     * @param[in] new_id:     舵机新ID
     * @retval none
    */
    void modify_servo_id(uint8_t new_id);
    /**
     * @brief          计算前n字节累加校验和
     * @param[in]      pch_message: 数据
     * @param[in]      dw_length: 数据和校验的长度
     * @retval         计算完的校验和
     */
    uint8_t get_check_sum(uint8_t *pch_message,uint32_t dw_length);
    /**
    * @brief     发送内容打包
    * @param[in] cmd_type:  命令内容ID
    * @param[in] *p_data: 数据段
    * @param[in] len:     数据段长度
    * @retval			返回要发送的数据大小
    */
    uint16_t send_servo_pack(uint8_t cmd_type, uint8_t *p_data, uint8_t len);

private:
    uint8_t servo_id;
    serial::Serial* SerialPtr_;
    static constexpr auto HEAD_SOF = 0x124C; //帧头
    uint8_t servo_tx_buffer[20];
    typedef enum
    {
        Ping_id = 0x01,      //检测舵机通讯
        Angle_set_id = 0x08, //舵机角度控制
        Angle_get_id = 0x0A, //舵机角度获取
        Modify_Id_id = 0x04, //修改舵机ID
        Angle_set_multi_id = 0x0D,//舵机角度控制 多圈
    }servo_cmd_e;
};

/**
 * D30舵机，PWM控制
*/
class D30 : public Servo
{
public:
    D30(Pwm *);
    ~D30();

    /**
	 * @brief          初始化硬件
	 * @param[in]      none
	 * @return  	   none
	*/
	void Init()
	{
		if(!pwm_->isEnable())
		{
			
		}
	}

    /**
     * @brief 设置舵机控制角度，单圈-135°~135°
     * @param[in] angle_set:  舵机角度
     * @retval none
    */
    void set_servo_angle(int16_t angle_set);

    /**
     * @brief 设置舵机上电初始角度，0°
     * @param[in] none
     * @retval none
    */
    void set_servo_initangle();

    /**
     * @brief 获取舵机角度
     * @retval none
    */
    int16_t get_servo_angle(void)
    {
        return this->curAngle_;
    }

    /**
     * @brief 舵机控制角度限幅，-135°~135°
     * @param[in] angle_set:  舵机角度
     * @retval none
    */
    int16_t limit_angle(int16_t angle_set);

private:
    Pwm *pwm_;
    int16_t initAngle_ = 0;
    int16_t curAngle_;
    static constexpr auto maxAngle_ = 135;
};

#endif /* _SERVO_HPP_ */
