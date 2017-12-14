#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 7, 6, 5, 4);

const int
TONE = 8,
R = 11,
G = 10,
B = 9,
TRIG = 2,
ECHO = 3;

double dis = 0;

void disDis(double dis){
  lcd.clear();
  lcd.home();
  lcd.print("distance");
  lcd.setCursor(0, 1);
  lcd.print(dis);
  lcd.print("cm");
}

void setRGB(int r, int g, int b){
  analogWrite(R, r);
  analogWrite(G, g);
  analogWrite(B, b);
}

double readDis(int EPin, int TPin){
  digitalWrite(TPin, LOW);delayMicroseconds(2);
  digitalWrite(TPin, HIGH);delayMicroseconds(10);
  digitalWrite(TPin, LOW);
  return pulseIn(EPin, HIGH)/58.0;
}

void setup() {
  for (int i = 8; i < 12;i++) pinMode(i, OUTPUT);
  pinMode(ECHO, INPUT);pinMode(TRIG, OUTPUT);
  noTone(TONE);
  lcd.begin(16, 2);
  disDis(0);
  setRGB(255, 0, 0);delay(1000);
  setRGB(0, 255, 0);delay(1000);
  setRGB(0, 0, 255);delay(1000);
  setRGB(0, 0, 0);delay(1000);
}

void loop() {
  disDis(dis = readDis(ECHO, TRIG));
}
