/**
*********************************************************************
*********
* @project_name :Four-wheeledCar
* @file : StatusList.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/1/21 
*********************************************************************
*********
*/
//
#include "StatusList.h"
EventGroupHandle_t externDataEventGroup;
HardwareSerial* SerialBSP;
void InitSerialBSP( uint32_t Bauds){
//    uint32_t Bauds=115200;
    SerialBSP= new HardwareSerial((USART1));
    SerialBSP->setRx(PA10);
    SerialBSP->setTx(PA9);
    SerialBSP->begin(Bauds);
    SerialBSP->println("Serial port initialized successfully");
    SerialBSP->print("serial port Bauds:");
    SerialBSP->println(Bauds);
}
void DeInitSerialBSP(){
    delete SerialBSP;
}
void setEventFlag(EventBits_t set){
    xEventGroupSetBits((EventGroupHandle_t) externDataEventGroup, /* 待操作的事件标志组句柄 */
                       (EventBits_t)set);
}