/**
*********************************************************************
*********
* @project_name :Four-wheeledCar
* @file : InteractiveProcess.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/1/21 
*********************************************************************
*********
*/
//

#ifndef FOUR_WHEELEDCAR_INTERACTIVEPROCESS_H
#define FOUR_WHEELEDCAR_INTERACTIVEPROCESS_H
#include "configureBT.h"
class interactiveProcess {
public:
    interactiveProcess();

    ~interactiveProcess();

    void upData();
protected:
    void commandAnalysis();
    void commandButton();
    void commandRocker();
    void contralForward(int &x, int& y);
    void contralBack(int &x, int& y);

    void contralLeft(int &x,int& y);
    void contralRight(int &x,int& y);
    void contralCircleRight(int &x,int& y);
    void contralCircleLeft(int &x,int& y);
private:
    uint8_t Mode;
//    String frameHeaderButton;
//    String frameHeaderRocker;
//    String frameTrailer;
    char command[15];

    HardwareSerial * BLTH;
};



#endif //FOUR_WHEELEDCAR_INTERACTIVEPROCESS_H
