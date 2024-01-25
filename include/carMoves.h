/**
*********************************************************************
*********
* @project_name :Four-wheeledCar
* @file : carMoves.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/1/20 
*********************************************************************
*********
*/
//

#ifndef FOUR_WHEELEDCAR_CARMOVES_H
#define FOUR_WHEELEDCAR_CARMOVES_H
#include <Arduino.h>
#include "STM32FreeRTOS.h"

class carMoves {


    callback_function_t timCallBack;
public:
    carMoves();
    ~carMoves();
    void CarMoveForward();
    void CarMoveStop();
    void CarMoveBack();
    void CarMoveLeft();
    void CarMoveRight();
    void CarMoveCircleLeft();
    void CarMoveCircleRight();
    void CarMoveLeftMoto();
    void CarMoveRightMoto();
    void CarMoveUpDataStatus();
    static uint8_t pwmValLeftInit;
    static uint8_t pwmValRightInit;
public:
    const uint8_t getPwmValLeftInit() const;

    const uint8_t getPwmValRightInit() const;

    const callback_function_t &getTimCallBack() const;

    void setTimCallBack(const callback_function_t &timCallBack);

    uint8_t getPwmValLeft() const;

    void setPwmValLeft(uint8_t pwmValLeft);

    uint8_t getPwmValRight() const;

    void setPwmValRight(uint8_t pwmValRight);

    uint8_t getPwmLeft() const;

    void setPwmLeft(uint8_t pwmLeft);

    uint8_t getPwmRight() const;

    void setPwmRight(uint8_t pwmRight);
protected:

    void MotorInit();
    void AvoidObstacles(EventBits_t&);
    void BlueThoothControl(EventBits_t&);
    void ControlHandle(EventBits_t&);
private:

    uint8_t pwmValLeft;
    uint8_t pwmValRight;
    uint8_t pwmLeft;
    uint8_t pwmRight;
    HardwareTimer* htim3;
    void SetGPIOH(uint32_t ulPin);
    void SetGPIOL(uint32_t ulPin);
};


#endif //FOUR_WHEELEDCAR_CARMOVES_H
