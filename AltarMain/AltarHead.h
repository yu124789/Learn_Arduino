#ifndef ALTARHEDD_H
#define ALTARHEDD_H

#include <Arduino.h>

class Altar {
private:
  int pin_LF, pin_LB, pin_RF, pin_RB;
  int pin_IR;
  int speed_;
public:
  Altar();
  ~Altar();
  
  Altar setSpeedA(int spd);

  int getSpeed();

  Altar goFront();
  Altar goBack();
  Altar turnLeft();
  Altar turnRight();
  Altar rotaLeft();
  Altar rotaRight();
  Altar stopA();
  
  void moveTest();
};

#endif
