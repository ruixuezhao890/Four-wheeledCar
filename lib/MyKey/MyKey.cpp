/**
*********************************************************************
*********
* @project_name :my_libarary
* @file : MyKey.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/8/31 
*********************************************************************
*********
*/
//

#include "MyKey.h"

vector<MyButton *> SaveButtonId;
ButtonManage buttonManage;
/***************************************************************
  *  @brief     函数作用 初始化按钮引脚
  *  @param     参数   portIndex：引脚分组 indexPin ：引脚号 ButtonId：按钮编号 activeLeve：触发电平
  *  @param     参数
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author    ZEN3
 **************************************************************/

MyButton::MyButton(uint32_t  pinIndex, uint8_t ButtonId, uint8_t activeLeve) {
    Manage=&buttonManage;
    this->pinIndex=pinIndex;
    if (activeLeve==0){
        pinMode(pinIndex, INPUT_PULLUP);
        digitalWrite(pinIndex, HIGH);
    }
    else{
        pinMode(pinIndex, INPUT_PULLDOWN);
        digitalWrite(pinIndex, LOW);
    }

    this->event=NONE_PRESS;
    this->button_level= digitalRead(pinIndex);
    this->active_level=activeLeve;
    this->button_id=ButtonId;
    this->state=0;
    for (int i = 0; i < number_of_event; ++i) {
        taskFunction[i]= nullptr;
    }

    //this->Ready=1;
}

MyButton::~MyButton() {

}
/***************************************************************
  *  @brief     函数作用 任务注册
  *  @param     参数   任务事件，回调函数指针
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author    ZEN3
 **************************************************************/

void MyButton::MyButtonTaskRegister(PressEvent event, BtnCallBack taskFunction) {
    this->taskFunction[event]=taskFunction;
}

/***************************************************************
  *  @brief     函数作用 得到现在按钮的事件
  *  @param     参数   无
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author    ZEN3
 **************************************************************/

PressEvent MyButton::GetNowEvent() {
    return (PressEvent)this->event;
}
/***************************************************************
  *  @brief     函数作用 使能当前的按钮
  *  @param     参数   无
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author    ZEN3
 **************************************************************/

void MyButton::MyButtonEnable() {
    SaveButtonId.push_back(this);
}
/***************************************************************
  *  @brief     函数作用 失能按钮
  *  @param     参数   无
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author    ZEN3
 **************************************************************/

void MyButton::MyButtonDisEnable() {
    for (auto it=SaveButtonId.begin(); it<SaveButtonId.end() ; ) {
        if((*it)->button_id==this->button_id){
            SaveButtonId.erase(it);
        }else{
            it++;
        }
    }
}

uint32_t MyButton::getPinIndex() const {
    return pinIndex;
}

/***************************************************************
  *  @brief     函数作用 轮询按键状态
  *  @param     参数   无
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author    ZEN3
 **************************************************************/
void ButtonManage::button_handler() {
    for (int i = 0; i < SaveButtonId.size(); ++i) {
        bool GPIOLevel= digitalRead(SaveButtonId[i]->getPinIndex());//获取当前的引脚电平
        if (SaveButtonId[i]->state>0)SaveButtonId[i]->ticks++;
        if (GPIOLevel!=SaveButtonId[i]->button_level){

            if (++(SaveButtonId[i]->debounce_cnt)>=DEBOUNCE_TICKS){
                SaveButtonId[i]->button_level=GPIOLevel;
                SaveButtonId[i]->debounce_cnt=0;
            }
        }else{
            SaveButtonId[i]->debounce_cnt=0;
        }
        switch (SaveButtonId[i]->state) {//状态机思想
            case 0:
                if (SaveButtonId[i]->button_level==SaveButtonId[i]->active_level){

                    SaveButtonId[i]->event=PRESS_DOWN;
                    TaskSelect(i,PRESS_DOWN);
                    SaveButtonId[i]->ticks=0;
                    SaveButtonId[i]->repeat=1;
                    SaveButtonId[i]->state=1;
                }else{
                    SaveButtonId[i]->event=NONE_PRESS;
                }
                break;
            case 1:
                if (SaveButtonId[i]->button_level!=SaveButtonId[i]->active_level){
                    SaveButtonId[i]->event=PRESS_UP;
                    TaskSelect(i,PRESS_UP);

                    SaveButtonId[i]->ticks=0;
                   // KeyU<<"1"<<endl;
                    SaveButtonId[i]->state=2;

                }
                else if (SaveButtonId[i]->ticks>LONG_TICKS){
                    SaveButtonId[i]->event=LONG_PRESS_START;
                    TaskSelect(i,LONG_PRESS_START);
                    SaveButtonId[i]->state=5;
                   // KeyU<<"5"<<endl;
                }

                break;
            case 2:
//                KeyU<<2<<endl;
                if (SaveButtonId[i]->button_level==SaveButtonId[i]->active_level){
                    SaveButtonId[i]->event=PRESS_DOWN;
                    //TaskSelect(i,PRESS_DOWN);
                    SaveButtonId[i]->repeat++;
                    TaskSelect(i,PRESS_REPEAT);
                    SaveButtonId[i]->ticks=0;
                    SaveButtonId[i]->state=3;
                }
                else if (SaveButtonId[i]->ticks>SHORT_TICKS){
                    if (SaveButtonId[i]->repeat==1){
                        SaveButtonId[i]->event=SINGLE_CLICK;
                        TaskSelect(i,SINGLE_CLICK);
                    }else if (SaveButtonId[i]->repeat==2){
                        SaveButtonId[i]->event=DOUBLE_CLICK;
                        //SaveButtonId[i]->taskFunction[DOUBLE_CLICK];
                        TaskSelect(i,DOUBLE_CLICK);
                    }
                    SaveButtonId[i]->state=0;
                }
                break;
            case 3:
               // KeyU<<3<<endl;
                if (SaveButtonId[i]->button_level!=SaveButtonId[i]->active_level){
                    SaveButtonId[i]->event=PRESS_UP;
                    TaskSelect(i,PRESS_UP);
                    //SaveButtonId[i]->taskFunction[PRESS_UP];
                    if (SaveButtonId[i]->ticks<SHORT_TICKS){
                        SaveButtonId[i]->ticks=0;
                        SaveButtonId[i]->state=2;
                    }else{
                        SaveButtonId[i]->state=0;
                    }

                }
                else if (SaveButtonId[i]->ticks>SHORT_TICKS){
                    SaveButtonId[i]->state=0;
                }
                break;
            case 5:
              //  KeyU<<5<<endl;
                if (SaveButtonId[i]->button_level==SaveButtonId[i]->active_level){
                    SaveButtonId[i]->event=LONG_PRESS_HOLD;
                   // SaveButtonId[i]->taskFunction[LONG_PRESS_HOLD];
                 TaskSelect(i,LONG_PRESS_HOLD);
                } else{
                    SaveButtonId[i]->event=PRESS_UP;
                    //SaveButtonId[i]->taskFunction[PRESS_UP];
                    TaskSelect(i,PRESS_UP);
                    SaveButtonId[i]->state=0;
                }
                break;
            default:
                SaveButtonId[i]->state=0;
                break;
        }
    }

}
/***************************************************************
  *  @brief     函数作用 执行对应回调函数
  *  @param     参数
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author    ZEN3
 **************************************************************/

uint8_t ButtonManage::TaskSelect(uint8_t i, PressEvent Event) {
    if (SaveButtonId[i]->taskFunction[Event]!= nullptr){
        SaveButtonId[i]->taskFunction[Event]();
        return 1;
    }
    return 0;
}

/***************************************************************
  *  @brief     函数作用 为按钮提供时基
  *  @param     参数   无
  *  @note      备注 ：时基是回调函数的五倍
  *  @Sample usage:     将该函数放入一个c语言能调用的函数中 再将那个函数放入中断函数
   * @author    ZEN3
 **************************************************************/

void ButtonManage::buttonTick() {
    time++;
    if (time>=5){
        time=0;
        this->button_handler();
    }
}

void ButtonManage::buttonRTOSTick() {
    this->button_handler();
}
