/**
*********************************************************************
*********
* @project_name :Four-wheeledCar
* @file : carMoves.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/1/20 
*********************************************************************
*********
*/
//

#include "carMoves.h"
#include "FreeOSTask.h"
#include "StatusList.h"
#include "EasyLogger.h"
#define SpeedVal 10
#define EN1 PB3              //电机驱动芯片L293D控制管脚EN1接PB1
#define EN2 PC13              //电机驱动芯片L293D控制管脚EN2接PB0

#define IN1 PA0              //电机驱动芯片L293D控制管脚IN1接PA0
#define IN2 PA1             //电机驱动芯片L293D控制管脚IN2接PA1
#define IN3 PA2             //电机驱动芯片L293D控制管脚IN3接PA2
#define IN4 PA3             //电机驱动芯片L293D控制管脚IN4接PA3
#define IN5 PA4             //电机驱动芯片L293D控制管脚IN5接PA4
#define IN6 PA5             //电机驱动芯片L293D控制管脚IN6接PA5
#define IN7 PA6             //电机驱动芯片L293D控制管脚IN7接PA6
#define IN8 PA7             //电机驱动芯片L293D控制管脚EN8接PA7
carMoves * gCarMoves;
uint8_t carMoves::pwmValLeftInit=SpeedVal;
uint8_t carMoves::pwmValRightInit=SpeedVal;
static void timeCallBack();
carMoves::carMoves()
{
    gCarMoves=this;
    setTimCallBack(timeCallBack);
    htim3=new HardwareTimer(TIM3);
    htim3->setOverflow(1000,HERTZ_FORMAT);
    htim3->setInterruptPriority(3,3);
    htim3->attachInterrupt(timCallBack);
    htim3->resume();
    pwmValRight=pwmValLeft=0;
    pwmLeft=pwmRight=1;
    MotorInit();
}

void carMoves::MotorInit() {
    pinMode(EN1,OUTPUT);SetGPIOH(EN1);
    pinMode(EN2,OUTPUT);SetGPIOH(EN2);
    pinMode(IN1,OUTPUT);SetGPIOH(IN1);
    pinMode(IN2,OUTPUT);SetGPIOH(IN2);
    pinMode(IN3,OUTPUT);SetGPIOH(IN3);
    pinMode(IN4,OUTPUT);SetGPIOH(IN4);
    pinMode(IN5,OUTPUT);SetGPIOH(IN5);
    pinMode(IN6,OUTPUT);SetGPIOH(IN6);
    pinMode(IN7,OUTPUT);SetGPIOH(IN7);
    pinMode(IN8,OUTPUT);SetGPIOH(IN8);
}

carMoves::~carMoves() {

}

void carMoves::SetGPIOH(uint32_t ulPin) {
    digitalWrite(ulPin,1);
}

void carMoves::SetGPIOL(uint32_t ulPin) {
    digitalWrite(ulPin,0);
}

void carMoves::CarMoveForward() {
//    SetGPIOH(EN1);
//    SetGPIOH(EN2);



        SetGPIOH(IN1);
        SetGPIOL(IN2);
        SetGPIOL(IN3);
        SetGPIOH(IN4);
        SetGPIOH(IN5);
        SetGPIOL(IN6);
        SetGPIOL(IN7);
        SetGPIOH(IN8);

}

void carMoves::CarMoveStop() {
    SetGPIOL(IN1);
    SetGPIOL(IN2);
    SetGPIOL(IN3);
    SetGPIOL(IN4);
    SetGPIOL(IN5);
    SetGPIOL(IN6);
    SetGPIOL(IN7);
    SetGPIOL(IN8);
}

void carMoves::CarMoveBack() {
    SetGPIOL(IN1);
    SetGPIOH(IN2);
    SetGPIOH(IN3);
    SetGPIOL(IN4);
    SetGPIOL(IN5);
    SetGPIOH(IN6);
    SetGPIOH(IN7);
    SetGPIOL(IN8);
}

void carMoves::CarMoveLeft() {
    SetGPIOH(IN1);
    SetGPIOL(IN2);
    SetGPIOL(IN3);
    SetGPIOH(IN4);
    SetGPIOL(IN5);
    SetGPIOL(IN6);
    SetGPIOL(IN7);
    SetGPIOL(IN8);
}

void carMoves::CarMoveRight() {
    SetGPIOL(IN1);
    SetGPIOL(IN2);
    SetGPIOL(IN3);
    SetGPIOL(IN4);
    SetGPIOH(IN5);
    SetGPIOL(IN6);
    SetGPIOL(IN7);
    SetGPIOH(IN8);
}

void carMoves::CarMoveCircleLeft() {
    SetGPIOH(IN1);
    SetGPIOL(IN2);
    SetGPIOL(IN3);
    SetGPIOH(IN4);
    SetGPIOL(IN5);
    SetGPIOH(IN6);
    SetGPIOH(IN7);
    SetGPIOL(IN8);
}

void carMoves::CarMoveCircleRight() {
    SetGPIOL(IN1);
    SetGPIOH(IN2);
    SetGPIOH(IN3);
    SetGPIOL(IN4);
    SetGPIOH(IN5);
    SetGPIOL(IN6);
    SetGPIOL(IN7);
    SetGPIOH(IN8);
}



const uint8_t carMoves::getPwmValLeftInit() const {
    return pwmValLeftInit;
}

const uint8_t carMoves::getPwmValRightInit() const {
    return pwmValRightInit;
}

const callback_function_t &carMoves::getTimCallBack() const {
    return timCallBack;
}

void carMoves::setTimCallBack(const callback_function_t &timCallBack) {
    carMoves::timCallBack = timCallBack;
}

uint8_t carMoves::getPwmValLeft() const {
    return pwmValLeft;
}

void carMoves::setPwmValLeft(uint8_t pwmValLeft) {
    carMoves::pwmValLeft = pwmValLeft;
}

uint8_t carMoves::getPwmValRight() const {
    return pwmValRight;
}

void carMoves::setPwmValRight(uint8_t pwmValRight) {
    carMoves::pwmValRight = pwmValRight;
}

uint8_t carMoves::getPwmLeft() const {
    return pwmLeft;
}

void carMoves::setPwmLeft(uint8_t pwmLeft) {
    carMoves::pwmLeft = pwmLeft;
}

uint8_t carMoves::getPwmRight() const {
    return pwmRight;
}

void carMoves::setPwmRight(uint8_t pwmRight) {
    carMoves::pwmRight = pwmRight;
}

void carMoves::CarMoveLeftMoto() {
    if (pwmLeft){
        if (pwmValLeft<=pwmValLeftInit){
            SetGPIOH(EN1);
        } else{
            SetGPIOL(EN1);
        }
        if (pwmValLeft>=20){
            pwmValLeft=0;
        }
    }else{
        SetGPIOL(EN1);
    }
}

void carMoves::CarMoveRightMoto() {
    if (pwmRight){
        if (pwmValRight<=pwmValRightInit){
            SetGPIOH(EN2);
        } else{
            SetGPIOL(EN2);
        }
        if (pwmValRight>=20){
            pwmValRight=0;
        }
    }else{
        SetGPIOL(EN2);
    }
}

void carMoves::CarMoveUpDataStatus() {
    auto r_event= xEventGroupWaitBits(externDataEventGroup,AllEVENT,
                                      pdFALSE,pdFALSE,portMAX_DELAY);

    if ((r_event&EVENT4)!=0) {//自动避障
//        LOG_DEBUG("CarMoveUpDataStatus"," Avoid");
        vTaskResume(TaskManage.externalDataHandle);
        AvoidObstacles(r_event);
    }
     if ((r_event&EVENT5)!=0){//蓝牙手动
         //LOG_DEBUG("CarMoveUpDataStatus"," BlueThooth");
         vTaskSuspend(TaskManage.externalDataHandle);
         BlueThoothControl(r_event);

    }
     if ((r_event&EVENT6)!=0){//循迹
         //LOG_DEBUG("CarMoveUpDataStatus"," Track");


    }

}

void carMoves::AvoidObstacles(EventBits_t &r_event) {
    pwmValLeftInit=pwmValRightInit=10;
    ControlHandle(r_event);
}

void carMoves::BlueThoothControl(EventBits_t & r_event) {
    ControlHandle(r_event);
}

void carMoves::ControlHandle(EventBits_t &r_event) {
    if ((r_event&EVENT1)!=0){

        xEventGroupClearBits(externDataEventGroup,EVENT1);

    }else if ((r_event&EVENT2)!=0){
        xEventGroupClearBits(externDataEventGroup,EVENT2);
        CarMoveCircleLeft();
    }else if ((r_event&EVENT3)!=0){
        xEventGroupClearBits(externDataEventGroup,EVENT3);
        // CarMoveRight();
        CarMoveCircleRight();
    }else if((r_event&EVENT7)!=0){
        xEventGroupClearBits(externDataEventGroup,EVENT7);

    }
    else if((r_event&EVENT14)!=0){
        xEventGroupClearBits(externDataEventGroup,EVENT14);
        CarMoveStop();
    }
    else if((r_event&EVENT15)!=0){
        xEventGroupClearBits(externDataEventGroup,EVENT15);
        CarMoveBack();
    }
    else if ((r_event&EVENT16)!=0){
        xEventGroupClearBits(externDataEventGroup,EVENT16);
        CarMoveForward();
    }
}

void timeCallBack(){
   gCarMoves->setPwmValLeft(gCarMoves->getPwmValLeft()+1);
   gCarMoves->setPwmValRight(gCarMoves->getPwmValRight()+1);
   gCarMoves->CarMoveLeftMoto();
   gCarMoves->CarMoveRightMoto();
}

