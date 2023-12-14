#ifndef _LED_HPP_
#define _LED_HPP_


#include "common.hpp"
#include "serial/serial.hpp"


class LED
{
public:
    LED(){};
    virtual ~LED(){};
    virtual void on(uint8_t brightness) = 0;
private:

};

/**
 * 霸勒斯LED灯，485通讯
*/
class Barlus : public LED
{
public:
    Barlus(serial::Serial* SerialPtr);
    ~Barlus() = default;

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
     * @brief 关闭LED灯
    */
    void off(void);
    /**
     * @brief 灯光增强
    */
   void enhance(void);
    /**
     * @brief 灯光减弱
    */
    void weaken(void);
    /**
     * @brief 灯光亮度存储
    */
    void save(void);
    /**
     * @brief 灯光亮度恢复
    */
    void recover(void);
    /**
     * @brief 开启灯光，亮度映射到0-255
     * 
    */
    void on(uint8_t brightness);

private:
    serial::Serial* SerialPtr_;
    uint8_t led_tx_buffer[7];
};

/**
 * SL LED灯，PWM控制
*/
class SL : public LED
{
public:
    SL(Pwm *pwm);
    ~SL();

    /**
	 * @brief          初始化硬件
	 * @param[in]      none
	 * @return  	   none
	*/
	void Init()
	{
		if(!pwm_->isEnable())
		{
			throw("pwm is not enable");
		}
	}

    /**
     * @brief 关闭LED灯
    */
    void off(void);

    /**
     * @brief 开启灯光，亮度映射到0-100
    */
    void on(uint8_t brightness);

private:   
    Pwm *pwm_;

};

#endif /* _LED_HPP_ */
