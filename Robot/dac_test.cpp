#include "dac_test.hpp"
#include "dac/dac.hpp"

static osThreadId dac_test_handle;

static void dac_test_task(void * argument)
{
    Dac dac(&hdac1);

    dac.setvalue(DAC_CHANNEL_1, 4095);
    dac.setvalue(DAC_CHANNEL_2, 4095);

    dac.start();

    if(!dac.isStart())
    {
        configASSERT(0);
    }

    while(1)
    {
        osDelay(1000);
    }
}

void dac_test_start(void)
{
    const osThreadAttr_t  dactestTask_attributes  = {
    .name = (char*)"dac_test",
    .stack_size = 512,
    .priority = osPriorityNormal,
    };
    dac_test_handle = osThreadNew(dac_test_task, NULL, &dactestTask_attributes);
}


