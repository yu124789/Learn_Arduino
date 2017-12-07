#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

#define MYDEBUG 0

IRrecv irc(2);
decode_results r;

const long
CHS = 0xFFA25D,
CH = 0x629D,
CHP = 0xFFE21D,
PREV = 0xFF22DD,
NEXT = 0xFF02FD,
PL_PA = 0xFFC23D,
VOLS = 0xFFE01F,
VOLP = 0xFFA857,
EQ = 0xFF906F,
K0 = 0xFF6897,
K100P = 0xFF9867,
K200P = 0xFFB04F,
K1 = 0xFF30CF,
K2 = 0xFF18E7,
K3 = 0xFF7A85,
K4 = 0xFF10EF,
K5 = 0xFF38C7,
K6 = 0xFF5AA5,
K7 = 0xFF42BD,
K8 = 0xFF4AB5,
K9 = 0xFF52AD,
DOWN = 0xFFFFFFFF;

typedef enum dir{STAY, NORTH, SOUTH, WEST, EAST}Dir;

class Snake {
  private:
    int len, spe;
    bool isStay;
    Dir nowDir;
    void setLenSpe(int len, int spe){
      this->len = len;
      this->spe = spe;
    }
  public:
    int snake[8*8][2];
    Snake(int x, int y){
      reset();
      setHead(x, y);
    }
    void setHead(int x, int y){
      snake[0][0] = x;
      snake[0][1] = y;
    }
    void getHead(int &x, int &y){
      x = snake[0][0];
      y = snake[0][1];
    }
    void mov(Dir d){
      if (d != STAY)
        for (int i = len; i > 0; i--){
          snake[i][0] = snake[i-1][0];
          snake[i][1] = snake[i-1][1];
        }
      switch (d){
        case STAY:isStay = true;break;
        case NORTH:if(0 == snake[0][0]--)snake[0][0] = 7;break;
        case SOUTH:if(7 == snake[0][0]++)snake[0][0] = 0;break;
        case WEST:if(0 == snake[0][1]--)snake[0][1] = 7;break;
        case EAST:if(7 == snake[0][1]++)snake[0][1] = 0;break;
      } 
      if(!isStay) nowDir = d;
      isStay = false;
    }
    void addLen(){
      len++;
      snake[len][0] = snake[len-1][0];
      snake[len][1] = snake[len-1][1];
      if (spe > 20 && len % 2 == 0)spe -= 2;
    }
    void getxy(int num, int &x, int &y){
      x = snake[num][0];
      y = snake[num][1];
    }
    int getLen(){
      return len;
    }
    int getSpe(){
      return spe;
    }
    Dir getNowDir(){
      return nowDir;
    }
    void reset(){
      setLenSpe(1, 50);
      nowDir = STAY;
      isStay = true;
    }
    bool eatSelf(){
      for (int i = 1; i < len; i++)
        if (snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1])
          return true;
      return false;
    }
};

class Food{
  private:
    int x,y;
  public:
    Food(int x, int y){
      this->x = x;
      this->y = y;
    }
    void getxy(int &x, int &y){
      x = this->x;
      y = this->y;
    }
    void setFood(int x, int y){
      this->x = x;
      this->y = y;
    }
    void reset(Snake &s){
      bool isOK = true;
      do{
        x = random(8);
        y = random(8);
        for (int i = 0; i < s.getLen(); i++)
          if (x == s.snake[i][0] && y == s.snake[i][1]) {
            isOK = false;
            break;
          }else{
            isOK = true;
          }
      }while(!isOK);
    }
};

class Led8x8 {
  private:
    char led8x8[8][8] = {{0}};
    int h[8] = {A0, A1, 12, 11, A5, A4, A3, A2};
    int l[8] = {10, 9, 8, 7, 6, 5, 4, 3};
  public:
    void Reset() {
      for (int i = 0; i < 8; i++) {
        digitalWrite(h[i], LOW);
        digitalWrite(l[i], HIGH);
      }
    }
    void SetPointHigh(int x, int y) {
      digitalWrite(h[y], HIGH);
      digitalWrite(l[x], LOW);
    }
    void InitLed() {
      for (int i = 0; i < 8; i++) {
        pinMode(h[i], OUTPUT);
        pinMode(l[i], OUTPUT);
      }
      Reset();
    }
    void Display() {
      for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
          if (led8x8[i][j]) SetPointHigh(i, j);
        }
        delay(1);
        Reset();
      }
    }
    void Clear(){
      for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
          led8x8[i][j] = 0;
    }
    void UpdateMap(Snake s, Food f){
      Clear();
      int sx, sy, fx, fy;
      f.getxy(fx, fy);
      led8x8[fy][fx] = 1;
      for (int i = 0; i < s.getLen(); i++){
        s.getxy(i, sx, sy);
        led8x8[sy][sx] = 1;
      }
    }
    bool EatFood(Snake &s, Food &f){
      int sx, sy, fx, fy;
      s.getHead(sx, sy);
      f.getxy(fx, fy);
      if (sx == fx && sy == fy) return true;
      return false;
    }
    void Welcome(){
      for (int i = 0; i < 8; i++){
        digitalWrite(h[i], LOW);
        digitalWrite(l[i], LOW);
      }
      for (int i = 0; i < 8; i++){
        digitalWrite(h[i], HIGH);
        delay(100);
      }
      for (int i = 0; i < 8; i++){
        digitalWrite(h[i], LOW);
        delay(100);
      }
    }
};

Led8x8 led8x8;
Snake snake(1, 1);
Food food (6,6);
Dir dir = STAY;

int count = 0;
bool 
gameOver = false,
once = true;

void setup() {
  Serial.begin(9600);
  irc.enableIRIn();
  led8x8.InitLed();
}

void loop() {
  if (irc.decode(&r)) {
#if MYDEBUG
  if (r.value != DOWN) Serial.println(r.value, HEX);
#endif
    switch (r.value){
      case EQ:gameOver = !gameOver;
      case K5:dir = STAY;break;
      case K2:if(snake.getNowDir() != SOUTH)dir = NORTH;break;
      case K8:if(snake.getNowDir() != NORTH)dir = SOUTH;break;
      case K4:if(snake.getNowDir() != EAST)dir = WEST;break;
      case K6:if(snake.getNowDir() != WEST)dir = EAST;break;
      default:break;
    } irc.resume();
  }
  if (!gameOver){
    if (once) {
      once = !once;
      led8x8.Welcome();
      led8x8.Reset();
    }
    if (count >= snake.getSpe()){
      count = 0;
      snake.mov(dir);
      if (snake.eatSelf()) {
        led8x8.Clear();
        snake.reset();
        food.reset(snake);
        led8x8.Welcome();
      }
      if (led8x8.EatFood(snake, food)){
        snake.addLen();
        food.reset(snake);
      }
#if MYDEBUG
    Serial.println("in debug:");
    Serial.println(snake.getLen());
    for (int i = 0; i < snake.getLen(); i++){
      Serial.println("------------");
      Serial.println(snake.snake[i][0]);
      Serial.println(snake.snake[i][1]);
      Serial.println(led8x8.EatFood(snake, food));
      Serial.println(snake.eatSelf());
      Serial.println("------------");
    }
#endif
    }
    count++;
    led8x8.UpdateMap(snake, food);
    led8x8.Display();
  }else{
    once = true;
  }
}

