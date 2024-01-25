/**
*********************************************************************
*********
* @project_name :Four-wheeledCar
* @file : StatusList.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/1/21 
*********************************************************************
*********
*/
//

#ifndef FOUR_WHEELEDCAR_STATUSLIST_H
#define FOUR_WHEELEDCAR_STATUSLIST_H
#include "STM32FreeRTOS.h"
#include "HardwareSerial.h"
extern HardwareSerial* SerialBSP;
void InitSerialBSP( uint32_t Bauds=115200);
void DeInitSerialBSP();
void setEventFlag(EventBits_t set);
#define EVENT1 (0x01 << 0)
#define EVENT2 (0x01 << 1)
#define EVENT3 (0x01 << 2)
#define EVENT4 (0x01 << 3)
#define EVENT5 (0x01 << 4)
#define EVENT6 (0x01 << 5)
#define EVENT7 (0x01 << 6)
#define EVENT8 (0x01 << 7)
#define EVENT9 (0x01 << 8)
#define EVENT10 (0x01 << 9)
#define EVENT11 (0x01 << 10)
#define EVENT12 (0x01 << 11)
#define EVENT13 (0x01 << 12)
#define EVENT14 (0x01 << 13)
#define EVENT15 (0x01 << 14)
#define EVENT16 (0x01 << 15)
#define AllEVENT EVENT1|EVENT2|EVENT3|EVENT4|EVENT5|EVENT6|EVENT7|EVENT8|EVENT9|EVENT10|EVENT11 |EVENT12 |EVENT13|EVENT14|EVENT15|EVENT16
extern EventGroupHandle_t externDataEventGroup;
#endif //FOUR_WHEELEDCAR_STATUSLIST_H
