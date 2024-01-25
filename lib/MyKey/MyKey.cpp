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
  *  @brief     �������� ��ʼ����ť����
  *  @param     ����   portIndex�����ŷ��� indexPin �����ź� ButtonId����ť��� activeLeve��������ƽ
  *  @param     ����
  *  @note      ��ע ����
  *  @Sample usage:     ������ʹ�÷��� ��ֱ�ӵ���
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
  *  @brief     �������� ����ע��
  *  @param     ����   �����¼����ص�����ָ��
  *  @note      ��ע ����
  *  @Sample usage:     ������ʹ�÷��� ��ֱ�ӵ���
   * @author    ZEN3
 **************************************************************/

void MyButton::MyButtonTaskRegister(PressEvent event, BtnCallBack taskFunction) {
    this->taskFunction[event]=taskFunction;
}

/***************************************************************
  *  @brief     �������� �õ����ڰ�ť���¼�
  *  @param     ����   ��
  *  @note      ��ע ����
  *  @Sample usage:     ������ʹ�÷��� ��ֱ�ӵ���
   * @author    ZEN3
 **************************************************************/

PressEvent MyButton::GetNowEvent() {
    return (PressEvent)this->event;
}
/***************************************************************
  *  @brief     �������� ʹ�ܵ�ǰ�İ�ť
  *  @param     ����   ��
  *  @note      ��ע ����
  *  @Sample usage:     ������ʹ�÷��� ��ֱ�ӵ���
   * @author    ZEN3
 **************************************************************/

void MyButton::MyButtonEnable() {
    SaveButtonId.push_back(this);
}
/***************************************************************
  *  @brief     �������� ʧ�ܰ�ť
  *  @param     ����   ��
  *  @note      ��ע ����
  *  @Sample usage:     ������ʹ�÷��� ��ֱ�ӵ���
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
  *  @brief     �������� ��ѯ����״̬
  *  @param     ����   ��
  *  @note      ��ע ����
  *  @Sample usage:     ������ʹ�÷��� ��ֱ�ӵ���
   * @author    ZEN3
 **************************************************************/
void ButtonManage::button_handler() {
    for (int i = 0; i < SaveButtonId.size(); ++i) {
        bool GPIOLevel= digitalRead(SaveButtonId[i]->getPinIndex());//��ȡ��ǰ�����ŵ�ƽ
        if (SaveButtonId[i]->state>0)SaveButtonId[i]->ticks++;
        if (GPIOLevel!=SaveButtonId[i]->button_level){

            if (++(SaveButtonId[i]->debounce_cnt)>=DEBOUNCE_TICKS){
                SaveButtonId[i]->button_level=GPIOLevel;
                SaveButtonId[i]->debounce_cnt=0;
            }
        }else{
            SaveButtonId[i]->debounce_cnt=0;
        }
        switch (SaveButtonId[i]->state) {//״̬��˼��
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
  *  @brief     �������� ִ�ж�Ӧ�ص�����
  *  @param     ����
  *  @note      ��ע ����
  *  @Sample usage:     ������ʹ�÷��� ��ֱ�ӵ���
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
  *  @brief     �������� Ϊ��ť�ṩʱ��
  *  @param     ����   ��
  *  @note      ��ע ��ʱ���ǻص��������屶
  *  @Sample usage:     ���ú�������һ��c�����ܵ��õĺ����� �ٽ��Ǹ����������жϺ���
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
