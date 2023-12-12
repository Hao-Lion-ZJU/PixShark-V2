#ifndef _CRAWLER_TASK_HPP_
#define _CRAWLER_TASK_HPP_

#include "RobotConfig.h"
#include "common.hpp"

#ifdef __cplusplus
extern "C" {
#endif


void crawler_task_start(void);
extern osThreadId crawler_task_handle;
extern int16_t crawler_speed[CRAWLER_NUM];

#ifdef __cplusplus
}
#endif

#endif /* _CRAWLER_TASK_HPP_ */

