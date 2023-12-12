#ifndef _ROBOT_CONFIG_H_
#define _ROBOT_CONFIG_H_

#define ROBOT_NAME "YellowRobot"
#define ROBOT_TYPE "ROV"
#define CONFIG_FW_VERSION 2.1
/**Communication config*/

#define MQTT_SERVER_IP  "192.168.1.121"


#define LED_PARAM       "brightness"
#define SERVO_PARAM     "servo_angle"
#define THRUSTER_TOPIC "/thruster"
#define ALTIMETER_TOPIC "/altimeter"
#define CRAWLER_TOPIC "/crawler"
#define DEPTH_TOPIC "/depth"
#define IMU_TOPIC "/imu"
#define CABIN_INFO_TOPIC "/cabin_info"


/**Motor config*/

#define CRAWLER_NUM 0           //履带电机数量,若未使用履带，赋0即可

#define Crawler_Left_ID 0x01    //左履带电机
#define Crawler_Right_ID 0x02   //右履带电机

/**Sensor config*/
#define DEPTH_FREQUNCY 20      //深度计请求频率


/**Thruster config*/
#define THRUSTER_NUM 6          //推进器数量
#define THRUSTER_MAX_RPM 3000   //推进器最大转速
#define THRUSTER_SLOW 3.95f //推进器减速比

#define Thruster_Vertical_Left_ID 0x40          //竖直方向左推进器
#define Thruster_Vertical_Right_ID 0x3f         //竖直方向右推进器
#define Thruster_Horizontal_TopLeft_ID 0x3e     //水平方向左上推进器
#define Thruster_Horizontal_TopRight_ID 0x3d    //水平方向右上推进器
#define Thruster_Horizontal_BottomRight_ID 0x42 //水平方向右下推进器
#define Thruster_Horizontal_BottomLeft_ID 0x41  //水平方向左下推进器




#endif /* _ROBOT_CONFIG_H_ */
