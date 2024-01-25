/**
*********************************************************************
*********
* @project_name :Four-wheeledCar
* @file : FreeLogger.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/1/22 
*********************************************************************
*********
*/
//

#ifndef FOUR_WHEELEDCAR_FREELOGGER_H
#define FOUR_WHEELEDCAR_FREELOGGER_H
#include "Arduino.h"
#include "STM32FreeRTOS.h"
#define LENGTH 15
#define SIZE 24
class FreeLogger{
private:
    QueueSetHandle_t messageQueue;
    uint8_t messageNum;
public:
    FreeLogger();
    void begin();
    void print(const char *buffer);
    void printFromISR(const char *buffer);
    void read();


};
//extern FreeLogger Logger;



#endif //FOUR_WHEELEDCAR_FREELOGGER_H
