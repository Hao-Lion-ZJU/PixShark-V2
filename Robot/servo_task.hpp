#ifndef _SERVO_TASK_HPP_
#define _SERVO_TASK_HPP_

#include "common.hpp"

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

extern osThreadId servo_task_handle;
extern uint8_t servo_angle;

void servo_task_start(void);

#ifdef __cplusplus
}
#endif



#endif /* _SERVO_TASK_HPP_ */
