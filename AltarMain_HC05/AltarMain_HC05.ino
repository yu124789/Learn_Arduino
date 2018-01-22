#include "AltarHead.h"

#include <IRremote.h>

//测得的红外遥控器按键编码
const long
CHS = 0xFFA25D, CH = 0xFF629D, CHP = 0xFFE21D,
PREV = 0xFF22DD, NEXT = 0xFF02FD, PLPA = 0xFFC23D,
VOLS = 0xFFE01F, VOLP = 0xFFA857, EQ = 0xFF906F,
D0 = 0xFF6897, D100P = 0xFF9867, D200P = 0xFFB04F,
D1 = 0xFF30CF, D2 = 0xFF18E7, D3 = 0xFF7A85,
D4 = 0xFF10EF, D5 = 0xFF38C7, D6 = 0xFF5AA5,
D7 = 0xFF42BD, D8 = 0xFF4AB5, D9 = 0xFF52AD;

Altar altar;

IRrecv irrecv(11);
decode_results results;

long code;
int aspd;
int count;
bool openT; //跟随
bool openIOA; //红外避障
bool openLT;  //寻线
bool hasBTS;
char mes;

void setup() {
#if MYDEBUG
  altar.moveTest();
#endif
  Serial.begin(38400); 
  irrecv.enableIRIn();
  count = 0;
  hasBTS = openT = openIOA = false;
}

void loop() {

  if (Serial.available()) {
    hasBTS = true;
    mes = Serial.read();
    switch (mes) {
      case '1': code = D2; break;
      case '2': code = D6; break;
      case '3': code = D8; break;
      case '4': code = D4; break;
      case '5': code = D3; break;
      case '6': code = D9; break;
      case '7': code = D7; break;
      case '8': code = D1; break;
      case '0':
      case 's':
      case 'S': code = D5; break;
      case 'g':
      case 'G': openT = !openT; break;
      case 'x':
      case 'X': openLT = !openLT; break;
      case 'b':
      case 'B': openIOA = !openIOA; break;
    }
  }

  if (irrecv.decode(&results) || hasBTS) {
    aspd = altar.getSpeed();
    if (!hasBTS) {
      code = results.value;
    }
    switch (code) {
      case D1: altar.turnLeft(); break;
      case D2: altar.goFront(); break;
      case D3: altar.turnRight(); break;
      case D4: altar.rotaLeft(); break;
      case D5: altar.stopA(); break;
      case D6: altar.rotaRight(); break;
      case D7: altar.turnLeftb(); break;
      case D8: altar.goBack(); break;
      case D9: altar.turnRightb(); break;
      case VOLS: altar.setSpeedA(aspd -= 5); break;
      case VOLP: altar.setSpeedA(aspd += 5); break;
      case EQ: altar.resetSpeed(); break;
      case PLPA: openT = !openT; break;
      case NEXT: openIOA = !openIOA; break;
      case PREV: openLT = !openLT; break;
    }
    irrecv.resume();
    hasBTS = false;
  }
  
  if (openT) {
    altar.T();
  }

  if (openLT) {
    altar.lineTracking();
  }

  if (openIOA) {
    altar.IOA();
  }

}
