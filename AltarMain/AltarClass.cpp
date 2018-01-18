#include "AltarHead.h"

Altar::Altar() {
  pinMode(pin_LF = 5, OUTPUT);
  pinMode(pin_LB = 10, OUTPUT);
  pinMode(pin_RF = 6, OUTPUT);
  pinMode(pin_RB = 9, OUTPUT);
  speed_ = 200;
}

Altar::~Altar() {
//  delete irrecvp;
}

Altar Altar::setSpeedA(int spd) {
  if (spd < 0) spd = 0;
  if (spd > 255) spd = 255;
  speed_ = spd;
  return *this;
}

int Altar::getSpeed() {
  return speed_;
}

Altar Altar::goFront() {
  analogWrite(pin_LB, 0);
  analogWrite(pin_RB, 0);
  analogWrite(pin_RF, speed_);
  analogWrite(pin_LF, speed_);
  return *this;
}

Altar Altar::goBack() {
  analogWrite(pin_LF, 0);
  analogWrite(pin_RF, 0);
  analogWrite(pin_RB, speed_);
  analogWrite(pin_LB, speed_);
  return *this;
}

Altar Altar::turnLeft() {
  analogWrite(pin_LF, 0);
  analogWrite(pin_RB, 0);
  analogWrite(pin_LB, 0);
  analogWrite(pin_RF, speed_);
  return *this;
}

Altar Altar::turnRight() {
  analogWrite(pin_LB, 0);
  analogWrite(pin_RF, 0);
  analogWrite(pin_RB, 0);
  analogWrite(pin_LF, speed_);
  return *this;
}

Altar Altar::rotaLeft() {
  analogWrite(pin_LF, 0);
  analogWrite(pin_RB, 0);
  analogWrite(pin_RF, speed_);
  analogWrite(pin_LB, speed_);
  return *this;
}

Altar Altar::rotaRight() {
  analogWrite(pin_LB, 0);
  analogWrite(pin_RF, 0);
  analogWrite(pin_LF, speed_);
  analogWrite(pin_RB, speed_);
  return *this;
}

Altar Altar::stopA() {
  analogWrite(pin_RF, 0);
  analogWrite(pin_LB, 0);
  analogWrite(pin_RB, 0);
  analogWrite(pin_LF, 0);
  return *this;
}

void Altar::moveTest() {
  goFront(); delay(400);
  stopA(); delay(500);
  goBack(); delay(400);
  stopA(); delay(500);
  rotaLeft(); delay(500);
  stopA(); delay(500);
  rotaRight(); delay(500);
  stopA();
}

