#ifndef _THRUSTER_TASK_HPP_
#define _THRUSTER_TASK_HPP_
#include "RobotConfig.h"
#include "common.hpp"


#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

extern osThreadId thruster_task_handle;
extern int16_t thruster_speed[THRUSTER_NUM];

void thruster_task_start(void);

#ifdef __cplusplus
}
#endif



#endif /* _THRUSTER_TASK_HPP_ */
