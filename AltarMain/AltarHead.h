#ifndef ALTARHEDD_H
#define ALTARHEDD_H

#define MYDEBUG 0

#include <Arduino.h>

#include <SR04.h>

typedef enum _MoveState {
  FRONT, BACK, STOP,
} MoveState;

class Altar {
  private:
    int pin_LF, pin_LB, pin_RF, pin_RB; //电机引脚
    int pin_IRLeft, pin_IRRight;  //红外避障引脚
    int pin_IRLeftx, pin_IRRightx;  //寻线引脚

    //超声波模块
    int pin_Echo, pin_Trig;
    SR04* sr04p;
    int distance_;

    int speed_;
    int upperDis_, lowerDis_; //最远和最近的距离
    MoveState moveState_;
  public:
    Altar();
    ~Altar();

    Altar setSpeedA(int spd);
    Altar setRange(int upperDis, int lowerDis);

    int getSpeed();
    int getDis();

    int keepDis();
    void keepDir();
    void lineTracking();

    Altar goFront();
    Altar goBack();
    Altar turnLeft();
    Altar turnRight();
    Altar rotaLeft();
    Altar rotaRight();
    Altar stopA();
#if MYDEBUG
    void moveTest();
    void IRTest(); //红外测试
#endif
};

#endif
