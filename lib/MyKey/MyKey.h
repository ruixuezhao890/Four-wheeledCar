/**
*********************************************************************
*********
* @project_name :my_libarary
* @file : MyKey.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/8/31 
*********************************************************************
*********
*/
//

#ifndef MY_LIBARARY_MYKEY_H
#define MY_LIBARARY_MYKEY_H
#include <Arduino.h>
#include "vector"
#include "map"
#define TICKS_INTERVAL    5	//ms
#define DEBOUNCE_TICKS    3	//MAX 7 (0 ~ 7)
#define SHORT_TICKS       (300 /TICKS_INTERVAL)
#define LONG_TICKS        (1000 /TICKS_INTERVAL)

using namespace std;


    typedef enum {
        PRESS_DOWN = 0,
        PRESS_UP,
        PRESS_REPEAT,
        SINGLE_CLICK,
        DOUBLE_CLICK,
        LONG_PRESS_START,
        LONG_PRESS_HOLD,
        number_of_event,
        NONE_PRESS
    }PressEvent;
	
    class MyButton;

    class ButtonManage {
    public:

        void button_handler();
        void buttonTick();
        void buttonRTOSTick();
        uint8_t TaskSelect(uint8_t i,PressEvent Event);


    protected:
        uint16_t time=0;

    };

    typedef void (*BtnCallBack)(void);
    class MyButton{
    private:
        uint32_t pinIndex;
        ButtonManage* Manage;
    public:
        uint8_t Ready;
        uint16_t ticks;
        uint8_t  repeat : 4;
        uint8_t  event : 4;
        uint8_t  state : 3;
        uint8_t  debounce_cnt : 3;
        uint8_t  active_level : 1;
        uint8_t  button_id;
        bool  button_level : 1;
        // uint8_t  (*hal_button_Level)(uint8_t button_id_);
        BtnCallBack taskFunction[number_of_event];
        MyButton(uint32_t pinIndex, uint8_t ButtonId, uint8_t activeLeve= 0);

        uint32_t getPinIndex() const;

        void MyButtonTaskRegister(PressEvent event,BtnCallBack taskFunction);
        void MyButtonEnable();
        void MyButtonDisEnable();
        PressEvent GetNowEvent();
        ~MyButton();
    };

extern vector<MyButton *> SaveButtonId;
extern ButtonManage buttonManage;
#endif //MY_LIBARARY_MYKEY_H
