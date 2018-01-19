#include "AltarHead.h"

Altar::Altar() {
  pinMode(pin_LF = 5, OUTPUT);
  pinMode(pin_LB = 10, OUTPUT);
  pinMode(pin_RF = 6, OUTPUT);
  pinMode(pin_RB = 9, OUTPUT);
  pinMode(pin_IRLeft = 8, INPUT);
  pinMode(pin_IRRight = 7, INPUT);
  pinMode(pin_IRLeftx = 4, INPUT);
  pinMode(pin_IRRightx = 2, INPUT);
  pinMode(pin_Echo = 12, INPUT);
  pinMode(pin_Trig = 13, OUTPUT);
  sr04p = new SR04(pin_Echo, pin_Trig);
  speed_ = 200;
  upperDis_ = 10; lowerDis_ = 5;
  moveState_ = STOP;
}

Altar::~Altar() {
  delete sr04p;
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
  moveState_ = FRONT;
  return *this;
}

Altar Altar::goBack() {
  analogWrite(pin_LF, 0);
  analogWrite(pin_RF, 0);
  analogWrite(pin_RB, speed_);
  analogWrite(pin_LB, speed_);
  moveState_ = BACK;
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
  moveState_ = STOP;
  return *this;
}

int Altar::getDis() {
  return distance_ = sr04p->Distance();
}

Altar Altar::setRange(int upperDis, int lowerDis) {
  upperDis_ = upperDis;
  lowerDis_ = lowerDis;
  return *this;
}

int Altar::keepDis() {
  int dis = getDis();
  if (dis > upperDis_) goFront();
  else if (dis < lowerDis_) goBack();
  else stopA();
  return dis;
}

void Altar::keepDir() {
  bool noLeft = digitalRead(pin_IRLeft);
  bool noRight = digitalRead(pin_IRRight);
  if (noLeft == noRight) {
    switch (moveState_) {
      case STOP: stopA(); break;
      case FRONT: goFront(); break;
      case BACK: goBack(); break;
    }
  } else if (noLeft) {
    turnRight();
  } else {
    turnLeft();
  }
}

void Altar::lineTracking() {

}

#if MYDEBUG
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
void Altar::IRTest() {
  Serial.print(digitalRead(pin_IRLeft));
  Serial.print(digitalRead(pin_IRRight));
  Serial.print(digitalRead(pin_IRLeftx));
  Serial.println(digitalRead(pin_IRRightx));
}
#endif

