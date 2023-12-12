#ifndef _DEPTH_HPP_
#define _DEPTH_HPP_



#include "common.hpp"
#include "serial/serial.hpp"

/* ----------------------- Data Struct ------------------------------------- */
#pragma pack(push, 1)


#pragma pack(pop)
/* ----------------------- extern Function ----------------------------------- */

/**
 * @brief   Depth 基类
*/
class Depth
{
public:
	Depth();
	virtual ~Depth(){}
	/**
	 * @brief          返回深度计数据指针
	*/
	float get_depth_data(void) const
	{
		return depth_data;
	}
	/**
	 * @brief          深度计协议解析
	 * @param[in]      depth_frame: 原生数据指针
	 * @return  	   none
	*/
	virtual void depth_data_solve(volatile const uint8_t *depth_frame) = 0;

	float depth_data;
};

class KELLER : public Depth
{

public:
	/**
	 * @brief   KELLER构造函数
	 * @param[in] dev_addr: 设备地址
	*/
	KELLER(serial::Serial* SerialPtr ,uint8_t dev_addr)
	{
		configASSERT(SerialPtr != nullptr);
  		this->dev_addr_ = dev_addr;
		this->SerialPtr_ = SerialPtr;
	}
	~KELLER(){}

	/**
	 * @brief          初始化硬件
	 * @param[in]      none
	 * @return  	   none
	*/
	void Init()
	{
		if(!SerialPtr_->isOpen())
		{
			SerialPtr_->open();	
		}
	}

	/**
	 * @brief          深度计协议解析，直接读取压力值，不进行modbus协议解析
	 * @param[in]      depth_frame: 原生数据指针
	 * @return  	   none
	*/
	void depth_data_solve(volatile const uint8_t *depth_frame);
	/**
	 * @brief          深度计协议解析，采用状态机方式解析modbus，比较规范
	 * @param[in]      none
	 * @return  	   none
	*/
	void depth_data_solve(void);

	/**
	 * @brief          深度计校准，采集大气压
	 * @param[in]      none
	 * @return  	   none
	*/
	void calibrate(void);

	/**
	 * @brief          读取深度计寄存器
	 * @param[in]      StAdd: 寄存器地址
	 * @param[in]      len: 需要读取的寄存器个数
	 * @return  	   none
	*/
	void read_register(uint16_t StAdd, uint8_t reg_len);
	/**
	 * @brief          写入深度计单个寄存器
	 * @param[in]      StAdd: 寄存器地址
	 * @param[in]      data: 数据
	*/
	void write_single_register(uint16_t StAdd, uint16_t data);
	/**
	 * @brief          请求读取一次压力值
	 * @param[in]      none
	 * @return  	   none
	*/
	void request_data(void);

public:
	static constexpr auto DEPTH_CMD_LENGTH = 8; //深度计发送缓冲区长度
	static constexpr auto DEPTH_DATA_LENGTH = 9; //深度计一帧数据长度
	

private:
	uint8_t dev_addr_;
	uint8_t depth_tx_buf[DEPTH_CMD_LENGTH]={0};

	bool is_calibrated = true;	//是否已经校准
	
	float atmosphere = 0.017f; 		//陆上气压,单位为bar

	serial::Serial *SerialPtr_;	//深度计串口指针

	typedef enum
	{
		Register_Read = 0x03,	//读寄存器
		Single_Register_Write = 0x06, //写单个寄存器
		Echo_Test = 0x08		//回传测试
	}depth_function;

	typedef enum
	{
		P1 = 0x0002,      //压力传感器1寄存器地址，单位bar
		P2 = 0x0004,      //压力传感器2寄存器地址，单位bar
		T =  0x0006,	 //温度，单位为℃
		UART  = 0x0200   //串口相关设置		
	}depth_StAdd;//更多地址参见科勒说明书



	
};

#endif /* _DEPTH_HPP_ */
