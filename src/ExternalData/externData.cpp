/**
*********************************************************************
*********
* @project_name :Four-wheeledCar
* @file : extenalData.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/1/21 
*********************************************************************
*********
*/
//

#include "externData.h"
#include "EasyLogger.h"
#include "Arduino.h"
#include "StatusList.h"
#define AvoidObstaclesLeft PA15
#define AvoidObstaclesRight PA12
externData::externData() {
    pinMode(AvoidObstaclesLeft,INPUT_PULLUP);
    pinMode(AvoidObstaclesRight,INPUT_PULLUP);
    carServo.attach(PB5,700,2600);//单位是微秒
    HCSR04.begin(PB1,PB0);
    carServo.write(90);
}

void externData::externDataUpData() {
    auto ret=xEventGroupGetBits(externDataEventGroup);
    if ((ret&EVENT4)!=0) {
        auto rec = HCSR04.measureDistanceCm();
        LOG_DEBUG("externDataUpData",*rec);
//    SerialBSP->println(*rec);
        if (((*rec) < 15.0 && (*rec) > 1.0) ||
            ((digitalRead(AvoidObstaclesLeft) == LOW) && (digitalRead(AvoidObstaclesRight) == LOW))) {
            setEventFlag(EVENT14);       /* 待设置的bit位 */
            osDelay(2000);
            judgeRunProcess();

        } else if ((digitalRead(AvoidObstaclesLeft) == HIGH) && (digitalRead(AvoidObstaclesRight) == LOW)) {
            setEventFlag(EVENT2);//左转
            osDelay(300);
        } else if ((digitalRead(AvoidObstaclesLeft) == LOW) && (digitalRead(AvoidObstaclesRight) == HIGH)) {
            setEventFlag(EVENT3);//右转
            osDelay(300);
        } else if (((*rec)==-1)||((*rec)>15)) {
            setEventFlag(EVENT16);       /* 待设置的bit位 */
        }
//

    }
}

void externData::judgeRunProcess() {
    carServo.write(180);
    auto recLeft=*HCSR04.measureDistanceCm();
    osDelay(1500);
    carServo.write(45);
    auto recRight=*HCSR04.measureDistanceCm();
    osDelay(1500);
    carServo.write(90);
    if ((recLeft)<20.0||(recRight)<20.0){
        setEventFlag(EVENT15);//后退
        osDelay(500);
    }
    if (recLeft>recRight){//左转
        setEventFlag(EVENT2);
        osDelay(400);
    }else if (recLeft<recRight){
        setEventFlag(EVENT3);
        osDelay(400);
    }

}

