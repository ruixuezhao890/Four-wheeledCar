/**
*********************************************************************
*********
* @project_name :Four-wheeledCar
* @file : FreeOSTask.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/1/20 
*********************************************************************
*********
*/
//

#ifndef FOUR_WHEELEDCAR_FREEOSTASK_H
#define FOUR_WHEELEDCAR_FREEOSTASK_H

#include <HardwareSerial.h>
#include "STM32FreeRTOS.h"
#include "EasyLogger.h"
class FreeOSTask {
public:

    FreeOSTask();
    ~FreeOSTask();
    void FreeOSTaskGreatTask();
    void FreeOSTaskStartSchedule();
  TaskHandle_t carMovesHandle={};
  TaskHandle_t externalDataHandle={};
  TaskHandle_t interactiveProcessHandle={};
  TaskHandle_t messagePrintHandle={};
};
extern  FreeOSTask TaskManage;

#endif //FOUR_WHEELEDCAR_FREEOSTASK_H
