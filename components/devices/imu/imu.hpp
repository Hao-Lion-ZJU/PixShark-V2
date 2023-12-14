#ifndef _IMU_HPP_
#define _IMU_HPP_

#include "common.hpp"
#include "serial/serial.hpp"


/* ----------------------- Data Struct ------------------------------------- */
#pragma pack(push, 1)	

typedef  struct
{
	//TODO: 添加IMU数据结构体
	//加速度 单位：g(9.8m/s)
	float Acc_x;
	float Acc_y;
	float Acc_z;
	//角度 单位：rad
	float Angle_x;
	float Angle_y;
	float Angle_z;
	//角速度 单位：rad/s
	float Gyrol_x;
	float Gyrol_y;
	float Gyrol_z;
} imu_data_t;

#pragma pack(pop)
/* ----------------------- extern Function ----------------------------------- */


/**
 * @brief   IMU 基类
*/
class IMU
{
public:
	IMU();
	virtual ~IMU() {}
	/**
	 * @brief          返回IMU数据指针
	*/
	imu_data_t get_imu_data(void) const
	{
		return imu_data;
	}
	/**
	 * @brief          IMU协议解析
	 * @param[in]      imu_frame: 原生数据指针
	 * @return  	   none
	*/
	virtual void imu_data_solve(volatile const uint8_t *imu_frame) = 0;

	
protected:
	imu_data_t imu_data;
};

/**
 * @brief   阿鲁比 IMU 具体型号：LPMS-IG1 mini
*/
class LPMS : public IMU
{
public:
	LPMS(serial::Serial *serialPtr);
	~LPMS() = default;

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
	 * @brief          IMU协议解析
	 * @param[in]      imu_frame: 原生数据指针
	 * @return  	   none
	*/
	void imu_data_solve(volatile const uint8_t *imu_frame);
	/**
	 * @brief          发送内容打包
	 * @param[in]      cmd_type:  命令内容ID
	 * @param[in]      p_data:  数据指针
	 * @param[in]      len:  数据长度
	 * @return  	   返回要发送的数据大小
	*/
	uint16_t send_pack(uint8_t cmd_type, uint8_t *p_data, uint16_t len);
	/**
	 * @brief          计算前n字节累加校验和
	 * @param[in]      LRC_message: 数据
	 * @param[in]      LRC_length: 数据和校验的长度
	 * @retval         计算完的校验和
	 */
	static uint8_t get_LRC_sum(uint8_t *LRC_message, uint16_t LRC_length){
		uint16_t check_sum = 0;
		uint16_t len = LRC_length;
		if (LRC_message == nullptr)
		{
			return 0XFF;
		}
		while(--len)
		{
			check_sum += *LRC_message++;
		}
		return check_sum;
	};

	/**
	 * @brief          LRC校验
	 * @param[in]      LRC_message: 数据
	 * @param[in]      LRC_length: 数据的长度
	 * @retval         计算完的校验和
	 */
	static bool LRC_check(uint8_t *data_message, uint32_t LRC_length){
		uint16_t temp = 0;
		uint16_t len = LRC_length;
		temp = get_LRC_sum(data_message, len-4);
		if(data_message[len-4] == (temp & 0xFF) && data_message[len-3] == (temp >> 8))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	};

	/**
	 * @brief 进入IMU命令模式
	 * @retval none
	*/
	void GOTO_Command_Mode(void);

	/**
	 * @brief 进入IMU数据流发送
	 * @retval none
	*/
	void GOTO_Streaming_Mode(void);

	/**
	 * @brief IMU参数保存
	 * @retval none
	*/
	void GOTO_Save_Setting(void);

public:
	static constexpr auto IMU_HEAD_SOF = 0x3A; //帧头
	static constexpr auto IMU_ID = 0x0001; //IMU设备ID
	static constexpr auto IMU_END_SOF = 0x0A0D; //帧尾
	static constexpr auto IMU_CMD_LENGTH = 11; //IMU指令长度
	static constexpr auto IMU_DATA_LENGTH = 167; //IMU回传数据大小
	static enum
	{
		Goto_Command_Mode_CMD   = 0x0006,  //进入命令模式
		Goto_Streaming_Mode_CMD = 0x0007, //进入数据发送模式
		Save_Setting_CMD        = 0x0004, //保存IMU参数设置

	}imu_cmd_e;

private:
	
	serial::Serial *SerialPtr_;	//IMU串口指针

	
	uint8_t imu_tx_buf[IMU_CMD_LENGTH]={0};
	
};

/**
 * @brief   北微传感 IMU 具体型号：
*/
class BWIMU : public IMU
{
public:
	BWIMU(serial::Serial *serialPtr);
	~BWIMU() = default;
	/**
	 * @brief          IMU协议解析
	 * @param[in]      imu_frame: 原生数据指针
	 * @return  	   none
	*/
	void imu_data_solve(volatile const uint8_t *imu_frame);
	/**
	 * @brief          发送内容打包
	 * @param[in]      cmd_type:  命令内容ID
	 * @param[in]      p_data:  数据指针
	 * @param[in]      len:  数据长度
	 * @return  	   返回要发送的数据大小
	*/
	uint16_t send_pack(uint8_t cmd_type, uint8_t *p_data, uint16_t len);
	/**
	 * @brief          IMU数据校验
	 * @param[in]      imu_frame: 原生数据指针
	 * @return  	   bool
	*/
	bool imu_check(uint8_t *data_message);

private:
	serial::Serial *SerialPtr_;	//IMU串口指针
};

class SC : public IMU
{
public:
	SC(serial::Serial *serialPtr);
	~SC() = default;

	/**
	 * @brief          IMU协议解析
	 * @param[in]      imu_frame: 原生数据指针
	 * @return  	   none
	*/
	void imu_data_solve(volatile const uint8_t *imu_frame);

	/**
	 * @brief          初始化硬件
	 * @param[in]      none
	 * @return  	   none
	*/
	void Init(void)
	{
		if(!SerialPtr_->isOpen())
		{
			SerialPtr_->open();	
		}
	}

	/**
	 * @brief          100D4软件复位
	 * @param[in]      none
	 * @return  	   none
	*/
	void Reset(void);

	/**
	 * @brief          IMU协议解析
	 * @param[in]      imu_frame: 原生数据指针
	 * @return  	   none
	*/
	void imu_data_solve(volatile const uint8_t *imu_frame) const;

	/**
	 * @brief          发送内容打包
	 * @param[in]      cmd_type:  命令内容ID
	 * @return  	   返回要发送的数据大小
	*/
	uint16_t send_pack(uint8_t cmd_type);

public:
	static constexpr auto IMU_CMD_LENGTH = 6; //IMU指令长度
	static constexpr auto IMU_DATA_LENGTH = 40; //IMU数据长度
	static constexpr auto IMU_HEADER_SOF = 0XA551; //IMU帧头
	static constexpr auto DATA_EOF = 0XAA; //IMU帧尾
	typedef enum
	{
		START_CMD_ID                 	= 0x01,
		STOP_CMD_ID                		= 0x02,
		CALIBRATION_CMD_ID             	= 0xE3,
		SAVE_CALIBRATION_CMD_ID         = 0xE1,
		OPEN_MAGNETIC_CORRECT_CMD_ID   	= 0xE2,
		CLOSE_MAGNETIC_CORRECT_CMD_ID  	= 0xE4,
	} imu_cmd_id_e;

private:
	serial::Serial *SerialPtr_;	//IMU串口指针

	uint8_t imu_tx_buf[IMU_CMD_LENGTH] = {0};

};

#endif /* _IMU_HPP_ */
