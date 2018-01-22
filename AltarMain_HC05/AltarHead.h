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

    /* 超声波模块 */
    int pin_Echo, pin_Trig;
    SR04* sr04p;
    int distance_;

    int speed_; //0~255
    int upperDis_, lowerDis_; //最远和最近的距离
    MoveState moveState_;
  public:
    Altar();
    ~Altar();

    Altar setSpeedA(int spd);
    Altar setRange(int upperDis, int lowerDis);

    Altar resetSpeed();

    int getSpeed();
    int getDis();
    MoveState getState();

    int keepDis();
    void keepDir();
    void lineTracking();
    void keepState();
    void IOA();
    void T();

    Altar goFront();
    Altar goBack();
    Altar turnLeft();
    Altar turnRight();
    Altar turnLeftb();
    Altar turnRightb();
    Altar rotaLeft();
    Altar rotaRight();
    Altar stopA();
#if MYDEBUG
    void moveTest();
    void IRTest(); //红外测试
#endif
};

#endif
