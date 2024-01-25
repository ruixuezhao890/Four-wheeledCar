/**
*********************************************************************
*********
* @project_name :Four-wheeledCar
* @file : main.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/1/20 
*********************************************************************
*********
*/
//
#include <Arduino.h>
#include "FreeOSTask.h"
void setup(void) {

    TaskManage.FreeOSTaskGreatTask();
    TaskManage.FreeOSTaskStartSchedule();
}
void loop(void) {

}