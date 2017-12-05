#include <NeoPixelAnimator.h>
#include <NeoPixelBrightnessBus.h>
#include <NeoPixelBus.h>

//定义LED灯串的基本属性
uint16_t PixelCount=12; //定义控制的个数
uint8_t pixelPin=7;     //定义引脚
NeoPixelBus<NeoGrbFeature,Neo800KbpsMethod> strip(PixelCount,pixelPin); //定义实例
HslColor lampHslColor;

struct Cmd {
  char head =  ' ';
  int num = 0;
}cmd;

bool isOpen = false;

void setup() {
 Serial.begin(38400);
 strip.Begin();
 strip.Show();

}

void setOFF(){
   for(int i=0;i<PixelCount;i++){
        strip.SetPixelColor(i,RgbColor(0));                    
      }
    strip.Show();
}

void loop() {
  if (Serial.available()){
    cmd.head = Serial.read();
    cmd.num = Serial.parseInt();
    switch (cmd.head){
      case 'H':lampHslColor.H = cmd.num/360.0f;break;
      case 'S':lampHslColor.S = cmd.num/100.0f;break;
      case 'L':lampHslColor.L = cmd.num/100.0f;break;
      case 'P':isOpen = !isOpen;
    }
    if (isOpen){
      for(int i=0;i<PixelCount;i++){
        strip.SetPixelColor(i,lampHslColor);
      }
      strip.Show();
    }else{
      setOFF();
    }
  }else{
    setOFF();
  }

}
