#ifndef CABIN_INFO_TASK_HPP
#define CABIN_INFO_TASK_HPP



#include "common.hpp"

typedef struct 
{
    float cabin_temperature;//舱内温度
    float cabin_humidity;//舱内湿度
    float cabin_water_level;//舱内水位
    float cpu_temperature;//CPU温度
}cabin_status_t;

#ifdef __cplusplus
extern "C" {
#endif

void cabin_info_task_start(void);

#ifdef __cplusplus
}
#endif

#endif /* CABIN_INFO_TASK_HPP */
