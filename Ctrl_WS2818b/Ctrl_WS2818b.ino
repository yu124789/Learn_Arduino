#include <NeoPixelAnimator.h>
#include <NeoPixelBrightnessBus.h>
#include <NeoPixelBus.h>

#define ON 1
#define OFF 0
#define DEBUG ON

//定义LED灯串的基本属性
uint16_t pixelCount = 12; //定义控制的个数
uint8_t pixelPin = 7;   //定义引脚
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(pixelCount, pixelPin); //定义实例
HslColor lampHslColor;

struct Cmd {
  char head =  ' ';
  float num = 0;
} cmd;

bool isOpen = false;

void setup() {
  Serial.begin(38400);
  strip.Begin();
  strip.Show();
}

void setOFF() {
  for (int i = 0; i < pixelCount; i++) {
    strip.SetPixelColor(i, RgbColor(0));
  }
  strip.Show();
}

void loop() {
  if (Serial.available()) {
    cmd.head = Serial.read();
    cmd.num = Serial.parseFloat();
    switch (cmd.head) {
      case 'H': lampHslColor.H = cmd.num; break;
      case 'S': lampHslColor.S = cmd.num; break;
      case 'L': lampHslColor.L = cmd.num; break;
      case 'P': isOpen = !isOpen;break;
      case 'C': isOpen = false;break;
    }
    if (isOpen) {
      for (int i = 0; i < pixelCount; i++) {
        strip.SetPixelColor(i, lampHslColor);
      }
      strip.Show();
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
