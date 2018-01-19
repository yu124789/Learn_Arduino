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
bool openSR04;
bool openIOA; //红外避障
bool openLT;  //寻线

void setup() {
#if MYDEBUG
  altar.moveTest();
#endif
  Serial.begin(9600);
  irrecv.enableIRIn();
  count = 0;
  openIOA = openSR04 = false;
}

void loop() {

  if (irrecv.decode(&results)) {
    aspd = altar.getSpeed();
    code = results.value;
#if MYDEBUG
    Serial.println(code, HEX);
#endif
    switch (code) {
      case D1: altar.turnLeft(); break;
      case D2: altar.goFront(); break;
      case D3: altar.turnRight(); break;
      case D4: altar.rotaLeft(); break;
      case D5: altar.stopA(); break;
      case D6: altar.rotaRight(); break;
      case D8: altar.goBack(); break;
      case VOLS: altar.setSpeedA(aspd -= 5); break;
      case VOLP: altar.setSpeedA(aspd += 5); break;
      case EQ: altar.setSpeedA(aspd = 200); break;
      case PLPA: openSR04 = !openSR04; break;
      case NEXT: openIOA = !openIOA; break;
    }
    irrecv.resume();
  }

  if (openSR04) {
    if (count++ == 32767) {
      count = 0;
      int dis = altar.keepDis();
#if MYDEBUG
      Serial.println(dis);
#endif
    }
  }

  if (openIOA) {
    altar.keepDir();
  }

  if (openLT) {
    altar.lineTracking();
  }

}
