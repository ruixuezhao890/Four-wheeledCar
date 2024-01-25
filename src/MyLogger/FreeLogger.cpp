/**
*********************************************************************
*********
* @project_name :Four-wheeledCar
* @file : FreeLogger.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/1/22 
*********************************************************************
*********
*/
//

#include "FreeLogger.h"
#include "StatusList.h"
//FreeLogger Logger;
FreeLogger::FreeLogger() {
    messageNum=0;

}
void FreeLogger::printFromISR(const char *buffer) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xQueueSendFromISR(messageQueue,&buffer,&xHigherPriorityTaskWoken);
}

void FreeLogger::print(const char *buffer) {
    auto ret=xQueueSend(messageQueue,&buffer,portMAX_DELAY);
    SerialBSP->println("ret:");
    SerialBSP->println(ret);

}

void FreeLogger::read() {
    char *buff;
    int ret=0;
    ret= xQueueReceive(messageQueue,&buff,portMAX_DELAY);
    if (ret!=pdFALSE){
        SerialBSP->println(buff);
    }
}

void FreeLogger::begin() {
    messageQueue=xQueueCreate(LENGTH,SIZE* sizeof(char*));
}
