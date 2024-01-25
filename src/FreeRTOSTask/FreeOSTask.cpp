/**
*********************************************************************
*********
* @project_name :Four-wheeledCar
* @file : FreeOSTask.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/1/20 
*********************************************************************
*********
*/
//

#include "FreeOSTask.h"
#include "StatusList.h"
#include "carMoves.h"
#include "externData.h"
#include "InteractiveProcess.h"
FreeOSTask TaskManage;
static void carMovesFunction(void const * argument);
static void externalDataFunction(void const * argument);
static void interactiveProcessFunction(void const * argument);
static void messagePrintFunction(void const * argument);

FreeOSTask::FreeOSTask() {
    InitSerialBSP();

}

FreeOSTask::~FreeOSTask() {
   DeInitSerialBSP();
}

void FreeOSTask::FreeOSTaskGreatTask() {
    taskENTER_CRITICAL();
    externDataEventGroup=xEventGroupCreate();
    LOG_DEBUG("RUN","RUN");
        xTaskCreate((TaskFunction_t )carMovesFunction,                 /* 任务函数 */
                (const char*    )"carMoves",               /* 任务名称 */
                (uint16_t       )512,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )osPriorityNormal,            /* 任务优先级 */
                (TaskHandle_t*  )&carMovesHandle);   /* 任务句柄 */

    xTaskCreate((TaskFunction_t ) externalDataFunction,                 /* 任务函数 */
                (const char*    )"ExternalData",               /* 任务名称 */
                (uint16_t       )512,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )osPriorityAboveNormal,            /* 任务优先级 */
                (TaskHandle_t*  )&externalDataHandle);   /* 任务句柄 */

    xTaskCreate((TaskFunction_t ) interactiveProcessFunction,                 /* 任务函数 */
                (const char*    )"interactiveProcess",               /* 任务名称 */
                (uint16_t       )512,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )osPriorityAboveNormal,            /* 任务优先级 */
                (TaskHandle_t*  )&interactiveProcessHandle);   /* 任务句柄 */
    taskEXIT_CRITICAL();            /* 退出临界区 */
}

void FreeOSTask::FreeOSTaskStartSchedule() {
    vTaskStartScheduler();
}
void carMovesFunction(void const * argument){
    LOG_DEBUG(" carMoves","RUN");
   carMoves CarMoves;
    for (;;){
        CarMoves.CarMoveUpDataStatus();
        osDelay(20);
    }
}
void externalDataFunction(void const * argument){

   externData externDataManage;
    for (;;){
       externDataManage.externDataUpData();
        osDelay(10);
    }
}
void interactiveProcessFunction(void const * argument){
    interactiveProcess interactiveData;
    for (;;){
        interactiveData.upData();
        osDelay(5);
    }
}
