/**
*********************************************************************
*********
* @project_name :Four-wheeledCar
* @file : InteractiveProcess.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/1/21 
*********************************************************************
*********
*/
//

#include "InteractiveProcess.h"
#include "EasyLogger.h"
#include "StatusList.h"
#include "carMoves.h"

interactiveProcess::interactiveProcess() {
    Mode=0;
    memset(command,0,15);
    BLTH=new HardwareSerial(USART3);
    BLTH->setTx(PB10);BLTH->setRx(PB11);
    BLTH->begin(115200);
    BLTH->println("Init UARAT3");

}

interactiveProcess::~interactiveProcess() {
    delete BLTH;
}

void interactiveProcess::upData() {
    commandAnalysis();
}

void interactiveProcess::commandAnalysis() {
    if (BLTH->available()){
        memset(command,0,15);
        for (int i = 0; i < 14; ++i) {
           command[i]=BLTH->read();
        }
        if ((command[0]!='0')&&
            (command[1]!='x')&&
            (command[2]!='5')&&
            (command[3]!='5')){
            return;
        }
        if ((command[10]!='0')&&
            (command[11]!='x')&&
            (command[12]!='6')&&
            (command[13]!='9')){
            return;
        }
        commandButton();
        auto ret=xEventGroupGetBits(externDataEventGroup);
        if ((ret&EVENT5)!=0) {
            commandRocker();
        }


    }


}

void interactiveProcess::commandButton() {

    if ((command[4]=='A')||(command[4]=='B')||(command[4]=='C')){
        LOG_DEBUG("USART3Rec","ABC");
        EventBits_t temp=32;
        switch (command[4]) {
            case 'A':
                BLTH->println("AvoidMode");
                xEventGroupClearBits(externDataEventGroup,EVENT5);
                xEventGroupClearBits(externDataEventGroup,EVENT6);
                xEventGroupSetBits((EventGroupHandle_t) externDataEventGroup,
                                   (EventBits_t) EVENT4);
                break;
            case 'B':
                BLTH->println("ControlMode");
                xEventGroupClearBits(externDataEventGroup,EVENT4);
                xEventGroupClearBits(externDataEventGroup,EVENT6);
                xEventGroupSetBits((EventGroupHandle_t) externDataEventGroup,
                                   (EventBits_t) EVENT5);
                break;
            case 'C':
                BLTH->println("TrackMode");
                xEventGroupClearBits(externDataEventGroup,EVENT5);
                xEventGroupClearBits(externDataEventGroup,EVENT4);
                xEventGroupSetBits((EventGroupHandle_t) externDataEventGroup,
                                   (EventBits_t) EVENT6);
                break;
            default:
                break;
        }
    }
}

void interactiveProcess::commandRocker() {
    if ((command[4] == 'X') || (command[7] == 'Y')) {
        LOG_DEBUG("USART3Rec","Rocker");
        if (command[5]=='X'&&command[6]=='X'){
            xEventGroupSetBits((EventGroupHandle_t) externDataEventGroup,
                               (EventBits_t) EVENT14);
            return;
        }
        char tempX[2] = {0};
        char tempY[2] = {0};
        tempX[0] = command[5];
        tempX[1] = command[6];
        tempY[0] = command[8];
        tempY[1] = command[9];
        int numberY = atoi(tempY);
        int numberX = atoi(tempX);

        LOG_DEBUG("RockerX", tempX);
        LOG_DEBUG("RockerY", tempY);
        if ((numberY>=40&&numberY<=60)){
            carMoves::pwmValLeftInit = carMoves::pwmValRightInit=10;
            if ((numberX>=0)&&(numberX<45)){//左转圈
                contralCircleLeft(numberX,numberY);
            }
            else if ((numberX>60)&&(numberX<99)){//右转圈
                contralCircleRight(numberX,numberY);
            }
            if (numberX>=40&&numberX<=60){
                xEventGroupSetBits((EventGroupHandle_t) externDataEventGroup,
                                   (EventBits_t) EVENT14);
            }
        }
        if (numberY>0&&numberY<40){
            contralForward(numberX,numberY);
        }
        if (numberY>60&&numberY<99){
            contralBack(numberX,numberY);
        }



    }
}

void interactiveProcess::contralForward(int& x, int &y) {
    uint8_t tempValSpeed = 0;
    if (y >= 10 && y < 15) {
        tempValSpeed = 18;
    } else if (y >= 15 && y < 20) {
        tempValSpeed = 16;
    } else if (y >= 20 && y < 30) {
        tempValSpeed = 14;
    } else if (y >= 30 && y <= 40) {
        tempValSpeed = 12;
    }
        if ((x>=0)&&(x<40)){//左
            carMoves::pwmValLeftInit=tempValSpeed-8;
            carMoves::pwmValRightInit=tempValSpeed;
        }
        else if ((x>60)&&(x<99)){//右转
            carMoves::pwmValLeftInit=tempValSpeed;
            carMoves::pwmValRightInit=tempValSpeed-8;
        }else{
            carMoves::pwmValLeftInit = carMoves::pwmValRightInit = tempValSpeed;
        }


    xEventGroupSetBits((EventGroupHandle_t) externDataEventGroup,
                       (EventBits_t) EVENT16);
}

void interactiveProcess::contralBack(int &x, int &y) {
    uint8_t tempValSpeed = 0;
    if (y >= 90 && y <100) {
        tempValSpeed = 18;
    } else if (y >= 80 && y < 90) {
        tempValSpeed = 16;
    } else if (y >= 70 && y < 80) {
        tempValSpeed = 14;
    } else if (y >= 60 && y <= 70) {
        tempValSpeed = 12;
    }
    if ((x>=0)&&(x<40)){//左
        carMoves::pwmValLeftInit=tempValSpeed-8;
        carMoves::pwmValRightInit=tempValSpeed;
    }
    else if ((x>60)&&(x<99)){//右转
        carMoves::pwmValLeftInit=tempValSpeed;
        carMoves::pwmValRightInit=tempValSpeed-8;
    }else{
        carMoves::pwmValLeftInit = carMoves::pwmValRightInit = tempValSpeed;
    }
    xEventGroupSetBits((EventGroupHandle_t) externDataEventGroup,
                       (EventBits_t) EVENT15);
}

void interactiveProcess::contralLeft(int &x, int &y) {


}

void interactiveProcess::contralRight(int &x, int &y) {

}

void interactiveProcess::contralCircleRight(int &x, int &y) {
    xEventGroupSetBits((EventGroupHandle_t) externDataEventGroup,
                       (EventBits_t) EVENT3);
}

void interactiveProcess::contralCircleLeft(int &x, int &y) {
    xEventGroupSetBits((EventGroupHandle_t) externDataEventGroup,
                       (EventBits_t) EVENT2);
}




