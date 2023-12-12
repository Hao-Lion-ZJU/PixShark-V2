#ifndef _SHT31_HPP_
#define _SHT31_HPP_

#include "common.hpp"
#include "i2c/i2c.hpp"

/* ----------------------- Data Struct ------------------------------------- */
typedef enum
{
    /* 软件复位命令 */

    SOFT_RESET_CMD = 0x30A2,	
    /*
    单次测量模式
    命名格式：Repeatability_CS_CMD
    CS： Clock stretching
    */
    HIGH_ENABLED_CMD    = 0x2C06,
    MEDIUM_ENABLED_CMD  = 0x2C0D,
    LOW_ENABLED_CMD     = 0x2C10,
    HIGH_DISABLED_CMD   = 0x2400,
    MEDIUM_DISABLED_CMD = 0x240B,
    LOW_DISABLED_CMD    = 0x2416,

    /*
    周期测量模式
    命名格式：Repeatability_MPS_CMD
    MPS：measurement per second
    */
    HIGH_0_5_CMD   = 0x2032,
    MEDIUM_0_5_CMD = 0x2024,
    LOW_0_5_CMD    = 0x202F,
    HIGH_1_CMD     = 0x2130,
    MEDIUM_1_CMD   = 0x2126,
    LOW_1_CMD      = 0x212D,
    HIGH_2_CMD     = 0x2236,
    MEDIUM_2_CMD   = 0x2220,
    LOW_2_CMD      = 0x222B,
    HIGH_4_CMD     = 0x2334,
    MEDIUM_4_CMD   = 0x2322,
    LOW_4_CMD      = 0x2329,
    HIGH_10_CMD    = 0x2737,
    MEDIUM_10_CMD  = 0x2721,
    LOW_10_CMD     = 0x272A,
	/* 周期测量模式读取数据命令 */
	READOUT_FOR_PERIODIC_MODE = 0xE000,
} SHT31_CMD;



class SHT31
{
public:
    SHT31(I2c* i2cPtr)
    {
        this->i2cPtr_ = i2cPtr;
    }
    ~SHT31() = default;

    /**
	 * @brief          初始化硬件
	 * @param[in]      none
	 * @return  	   none
	*/
	void Init()
	{
		if(!i2cPtr_->isOpen())
		{
			i2cPtr_->open();	
		}
	}

    /**
     * @brief          向SHT31发送一条指令(16bit)
     * @param[in]      cmd: 命令 （在SHT31_MODE中枚举定义）
     * @retval         none
    */
    void send_cmd(SHT31_CMD cmd);
    /**
     * @brief          软件复位
     * @param[in]      none
     * @retval         none
    */
    void reset();
    /**
     * @brief          读取数据
     * @param[out]     temperature: 温度
     * @param[out]     humidity: 湿度
     * @retval         none
    */
    void read_data(float &temperature, float &humidity);

    static constexpr auto WRITE_ADDR = 0x88; //sht31写地址
    static constexpr auto READ_ADDR = 0x89; //sht31读地址

private:
    I2c* i2cPtr_;

};



#endif /* _SHT31_HPP_ */
