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

/* display distance. */
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

/* read distance. */
double readDis(int EPin, int TPin){
  digitalWrite(TPin, LOW);delayMicroseconds(2);
  digitalWrite(TPin, HIGH);delayMicroseconds(10);
  digitalWrite(TPin, LOW);
  return pulseIn(EPin, HIGH)/58.0;//cm
}

void buzzing(int hz, int interval){
  static int bc = 0;//buzzing count.
  if (++bc >= interval) {
    bc = 0;
    tone(TONE, hz);
  }else if (bc >= interval/2) noTone(TONE);
}

void setup() {
  for (int i = 8; i < 12;i++) pinMode(i, OUTPUT);//rgb+tone
  pinMode(ECHO, INPUT);pinMode(TRIG, OUTPUT);//sr40
  /* initialize. */
  noTone(TONE);
  lcd.begin(16, 2);
  /* test. */
  disDis(0);
  setRGB(255, 0, 0);delay(500);
  setRGB(0, 255, 0);delay(500);
  setRGB(0, 0, 255);delay(500);
  setRGB(0, 0, 0);
}

int c = 0;//count.
void loop() {
  delay(1);
  if (1000 <= c++){
    c = 0;
    disDis(dis = readDis(ECHO, TRIG));//read distance and display it to lcd.
  }
  if (12 >= dis){
    setRGB(255, 0, 0);//red
    buzzing(900, 300);
  }else if (15 >= dis){
    setRGB(255, 255, 0);//yellow
    buzzing(800, 400);
  }else if (18 >= dis){
    setRGB(0, 255, 0);//green
    buzzing(700, 500);
  }else{
    /* close. */
    setRGB(0, 0, 0);
    noTone(TONE);
  }
}

