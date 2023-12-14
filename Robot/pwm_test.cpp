#include "pwm_test.hpp"
#include "pwm/pwm.hpp"

static osThreadId pwm_test_handle;

static void pwm_test_task(void * argument)
{
    Pwm pwm1(&htim8, TIM_CHANNEL_1);
    Pwm pwm2(&htim8, TIM_CHANNEL_2);

    pwm1.enable(100, 50);
    pwm2.enable(100, 50);

    if(!pwm1.isEnable() || !pwm2.isEnable())
    {
        configASSERT(0);
    }

    uint8_t i = 0;

    // for(;;)
    // {
    //     if(i > 100)
    //     {
    //         i = 0;
    //         continue;
    //     }
    //     else
    //     {
    //         pwm1.setDutyCycle(i);
    //         pwm2.setDutyCycle(i);
    //         i++;
    //     }
    //     osDelay(1000);
    // }

}

void pwm_test_start(void)
{
    const osThreadAttr_t  pwmtestTask_attributes  = {
    .name = (char*)"pwm_test",
    .stack_size = 512,
    .priority = osPriorityNormal,
    };
    pwm_test_handle = osThreadNew(pwm_test_task, NULL, &pwmtestTask_attributes);
}


