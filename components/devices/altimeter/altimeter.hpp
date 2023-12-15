#ifndef _ALTIMETER_HPP_
#define _ALTIMETER_HPP_

#include "common.hpp"
#include "serial/serial.hpp"
/* ----------------------- Data Struct ------------------------------------- */
#pragma pack(push, 1)


#pragma pack(pop)
/* ----------------------- extern Function ----------------------------------- */

/**
 * @brief   高度计基类
*/
class Altimeter
{
public:
	Altimeter();
	virtual ~Altimeter()
	{
		
	}
	/**
	 * @brief          返回高度计数据指针
	*/
	float get_altimeter_data(void) const
	{
		return altimeter_data;
	}
	/**
	 * @brief          高度计协议解析
	 * @param[in]      depth_frame: 原生数据指针
	 * @return  	   none
	*/
	virtual void altimeter_data_solve(volatile const uint8_t *depth_frame) = 0;

	

	float altimeter_data;		//高度,单位为m
};

class ISA500 : public Altimeter
{
public:
	ISA500(serial::Serial *serialPtr);
	~ISA500()
	{

	}
	/**
	 * @brief          初始化硬件
	 * @param[in]      none
	 * @return  	   none
	*/
	void Init()
	{
		if(!SerialPtr_->isOpen())
		{
			SerialPtr_->open(O_RDONLY);	
		}
	}
	/**
	 * @brief          高度计协议解析
	 * @param[in]      depth_frame: 原生数据指针
	 * @return  	   none
	*/
	void altimeter_data_solve(volatile const uint8_t *depth_frame);
public:
	/**这里高度计为ASCII字符输出，设置ID为107，即ddd.ddm<CR><LF>*/
	static constexpr auto AM_DATA_LENGTH = 9; //高度计上传数据长度
	serial::Serial *SerialPtr_;	//高度计串口指针

};

class P30 : public Altimeter
{
public:
	P30(serial::Serial *serialPtr);
	~P30();
	/**
	 * @brief          初始化硬件
	 * @param[in]      none
	 * @return  	   none
	*/
	void Init()
	{
		if(!SerialPtr_->isOpen())
		{
			SerialPtr_->open(O_RDWR);	
		}
	}
	/**
	 * @brief          获取一次简单数据
	 * @param[in]      none
	 * @return  	   none
	*/
	void request_data(void);
	/**
	 * @brief          高度计协议解析
	 * @param[in]      depth_frame: 原生数据指针
	 * @return  	   none
	*/
	void altimeter_data_solve(volatile const uint8_t *depth_frame);
	
public:
	static constexpr auto AM_CMD_LENGTH = 15;  //高度计下发指令的指令长度
	static constexpr auto AM_DATA_LENGTH = 15; //高度计上传数据长度
	uint8_t cmd_tx_buf[AM_CMD_LENGTH] = {0};
	serial::Serial *SerialPtr_;	//高度计串口指针

};

#endif /* _ALTIMETER_HPP_ */
