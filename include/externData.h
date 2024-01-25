/**
*********************************************************************
*********
* @project_name :Four-wheeledCar
* @file : extenalData.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/1/21 
*********************************************************************
*********
*/
//

#ifndef FOUR_WHEELEDCAR_EXTENALDATA_H
#define FOUR_WHEELEDCAR_EXTENALDATA_H
#include "carMoves.h"
#include "Servo.h"
#include "HCSR04.h"
class externData {
public:
    externData();
    void externDataUpData();
protected:
    void judgeRunProcess();
private:
    Servo carServo;
};


#endif //FOUR_WHEELEDCAR_EXTENALDATA_H
