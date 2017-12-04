bool isL = false;

void setup() {
 Serial.begin(38400);
 pinMode(13, OUTPUT);
}

void loop() {
  while(Serial.available()){
      digitalWrite(13,isL = !isL);
    }
  }
}
