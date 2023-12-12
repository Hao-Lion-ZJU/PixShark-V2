#ifndef _GPS_HPP_
#define _GPS_HPP_


#include "common.hpp"
#include "serial/serial.hpp"
/* ----------------------- Data Struct ------------------------------------- */
#pragma pack(push, 1)

typedef  struct
{
	//TODO: 添加gps数据结构体
	float latitude;       //正数为北纬，负数为南纬
    float longitude;      //正数为东经，负数为西经
} gps_data_t;	

#pragma pack(pop)
/* ----------------------- extern Function ----------------------------------- */


/**
 * @brief   GPS 基类
*/
class GPS
{
public:
	GPS();
	virtual ~GPS() {}
	/**
	 * @brief          返回GPS数据指针
	*/
	gps_data_t get_gps_data_point(void) const
	{
		return gps_data;
	}
	/**
	 * @brief          GPS协议解析
	 * @param[in]      gps_frame: 原生数据指针
	 * @return  	   none
	*/
	virtual void gps_data_solve(volatile const uint8_t *gps_frame) = 0;

	
protected:
	gps_data_t gps_data;
};

#endif /* _GPS_HPP_ */
