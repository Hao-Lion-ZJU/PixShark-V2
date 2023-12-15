#ifndef _THRUSTER_HPP_
#define _THRUSTER_HPP_

#include "common.hpp"
#include "can/can.hpp"


class Thruster
{
public:
    Thruster()
    {

    }
    virtual ~Thruster(){};
    virtual void set_expect_speed(int32_t speed_set) = 0;
    virtual int16_t get_rpm() = 0;
protected:

};


class VESC : public Thruster
{
public:
    VESC(Can* canPtr ,uint32_t id)
    {
        this->thruster_id_ = id;
        this->canPtr_ = canPtr;
    }
    ~VESC(){};

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
    
    /**
     * @brief 设置推进器期望转速,单位rpm
     * @param rpm_set 转速值
     * @return None
    */
    void set_expect_speed(int32_t rpm_set);
    void set_status(int32_t rpm_feedback, int16_t current_feedback, int16_t duty_feedback)
    {
        this->thruster_status_msg_.rpm = rpm_feedback;
        this->thruster_status_msg_.current = current_feedback;
        this->thruster_status_msg_.duty = duty_feedback;
    }
    int16_t get_rpm()
    {
        return this->thruster_status_msg_.rpm;
    }
    /**
     * @brief 设置推进器期望电流,单位mA
     * @param current_set 电流值
     * @return None
    */
    void set_expect_current(int32_t current_set);

public:
    static constexpr auto THRUSTER_POLAR_PARIS_NUM = 3;  //推进器极对数

    static enum {
    CAN_PACKET_SET_DUTY = 0,
    CAN_PACKET_SET_CURRENT = 1,
    CAN_PACKET_SET_RPM = 3,
    CAN_PACKET_SET_POS = 4,
    CAN_PACKET_STATUS = 9,
    } CAN_PACKET_ID;  //VESC CAN commands，可以在源码里面看到完整定义
private:
    Can* canPtr_;
    uint8_t thruste_tx_buffer[8];
    uint32_t thruster_id_; 
    struct {
        int32_t rpm;
        int16_t current;
        int16_t duty;
    } thruster_status_msg_;  //回传电机状态
    // CAN commands


};

class FUBER : public Thruster
{
public:
    FUBER(Can* canPtr ,uint32_t id)
    {
        this->thruster_id_ = id;
        this->canPtr_ = canPtr;
    }
    ~FUBER(){};

    typedef enum
    {
        THRUSTER_OK = 0, //推进器无故障
        THRUSTER_FAULT = 1, //推进器故障
    } motor_fault_status_e;

    typedef enum
    {
        CAN_ID_BASE = 0X201, //推进器CAN ID基数
        CAN_M1_ID = 0X202, //控制帧
        CAN_M2_ID = 0X203, //控制帧
        CAN_M3_ID = 0X204, //控制帧
        CAN_M4_ID = 0X205, //控制帧
        CAN_M5_ID = 0X206, //控制帧
        CAN_M6_ID = 0X207, //控制帧
        CAN_MOTOR_PARAM_REQUEST_ID = 0X300, //电机参数请求帧
        CAN_RETURN_ID = 0X18, //确认返回帧
        CAN_MOTOR_PARAM_ID = 0X38, //电机参数帧
        CAN_CONTROL_PARAM_ID = 0X60, //控制参数配置帧
    } can_msg_id_e;

    typedef struct 
    {
        uint16_t speed_rpm; //电机转速
        float given_voltage; //母线电压
        float given_current; //母线电流
        uint8_t controller_temperate; //控制器温度
        uint8_t motor_temperate; //电机温度
        uint8_t motor_status; //电机状态
    } thruster_status_msg_;  //回传电机状态

    // CAN commands
    typedef enum
    {
        MODE=0x0001,									//设置控制模式，00为模拟量控制
        POLE_COUPLE=0x0003,						//设置电机的极对数，默认为3，无需更改
        TEMPERATE_PROTECT=0x0008,			//电机过温保护，默认为70℃
        Speed_Kp=0x000D,							//速度环Kp，默认3000
        Speed_Ki=0x000E,							//速度环Ki，默认20	
        Current_Kp=0x000F,						//电流环Kp，默认100
        Current_Ki=0x0010,						//电流环Ki，默认20
        CAN_Buadrate=0x0014,					//CAN通讯波特率设置 4:1M 8:500K 16:250K
        CAN_Upload=0x0015,						//CAN上传间隔 默认250ms
        CAN_Timeout=0x0016,						//CAN通讯超时时间 默认3000ms
        Init_Angle=0x0020,						//初始角学习
        Factory_Reset=0xEEEE,					//恢复默认出厂设置
        Save_Param=0xFFFF,						//保存控制器配置参数
    } controller_param_set_e;

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

    /**
	 * @brief          推机器预初始化
	 * @param[in]      none
	 * @return  	   none
	*/
	void thruster_init(void);

    /**
  * @brief          发送推进器控制帧
  * @param[in]      Motor_ID: 推进器ID
  * @param[in]      velocity: 控制推进器转速, 范围 [-3500,3500]
  * @param[in]      ACK_MODE: 设置回传模式  0X00：200ms自动上传     0xAA：收到指令回传
  * @retval         none
  */
    void cmd_control(int16_t velocity, uint8_t ACK_MODE);

    int16_t get_rpm()
    {
        return motor_param_t.speed_rpm;
    }

    /**
    * @brief          配置推进器控制器参数
    * @param[in]      _parm: 控制器参数索引
    * @param[in]      value: 参数配置值
    * @retval         none
    */
    void set_controler(controller_param_set_e _param, uint16_t value);

    /**
    * @brief          应答模式下请求电机参数回传
    * @param[in]      MOTOR_ID: 推进器ID
    * @retval         none
    */
    void param_request(void);

    /**
    * @brief          读取电机状态数据
    * @param[in]      MOTOR_ID: 推进器ID
    * @retval         none
    */
    void thrust_status_get(void);


private:

    Can *canPtr_;
    static constexpr auto max_speed = 2400;
    uint8_t thrust_tx_buffer[8];
    uint32_t thruster_id_;
    thruster_status_msg_ motor_param_t;

};

#endif /* _THRUSTER_HPP_ */
