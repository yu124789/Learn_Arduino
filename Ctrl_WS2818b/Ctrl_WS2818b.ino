
#include <Adafruit_NeoPixel.h>

#define ON 1
#define OFF 0
#define DEBUG ON

int r,g,b;

//定义LED灯串的基本属性
uint16_t pixelCount = 9; //定义控制的个数
uint8_t pixelPin = 6;   //定义引脚
Adafruit_NeoPixel strip(pixelCount, pixelPin, NEO_RGB + NEO_KHZ800); //定义实例
uint32_t color = strip.Color(0, 0, 0);

struct Cmd {
  char head =  ' ';
  int num = 0;
} cmd;

bool isOpen = false;

void setup() {
  r = g = b = 0;
  Serial.begin(38400);
  strip.begin();
  strip.show();
}

void setOFF() {
  for (int i = 0; i < pixelCount; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}

void loop() {
  if (Serial.available()) {
    cmd.head = Serial.read();
    cmd.num = (int)Serial.parseFloat();
    switch (cmd.head) {
      case 'R':  r = cmd.num; break;
      case 'G':  g = cmd.num; break;
      case 'B':  b = cmd.num; break;
      case 'P': isOpen = !isOpen;break;
      case 'C': isOpen = false;break;
    }
    if (isOpen) {
      for (int i = 0; i < pixelCount; i++) {
        strip.setPixelColor(i, strip.Color(r, g, b));
      }
      strip.show();
    } else {
      setOFF();
    }
#if DEBUG
Serial.print("head:");Serial.println(cmd.head);
Serial.print("num:");Serial.println(cmd.num);
Serial.print("isOpen:");Serial.println(isOpen);
Serial.print("pixelCount:");Serial.println(pixelCount);
Serial.println("---------");
#endif
  } 
}
