#include "can_test.hpp"
#include "can/can.hpp"

static osThreadId can_test_handle;

static void can_test_task(void * argument)
{
    Can can(&hfdcan1);

    //can.setfilter(FDCAN_STANDARD_ID, 0, 0x0000, 0x0000);

    can.setTimeout(osWaitForever);

    can.start();
    if(!can.isStart())
    {
        configASSERT(0);
    }

    uint8_t sendBuf[3] = {1};
    uint8_t recvBuf[8] = {0};
    uint32_t Id, Id_type;
    for(;;)
    {
        // can.sendto(0x123,sendBuf, 3);
        can.recvfrom(Id, Id_type, recvBuf);
        can.sendto(0x123, recvBuf, 8);
        vTaskDelay(1000);
    }

}

void can_test_start(void)
{
    const osThreadAttr_t  cantestTask_attributes  = {
    .name = (char*)"can_test",
    .stack_size = 256,
    .priority = osPriorityRealtime,
    };
    can_test_handle = osThreadNew(can_test_task, NULL, &cantestTask_attributes);
}


