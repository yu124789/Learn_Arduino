void setup() {
 Serial.begin(38400);
 pinMode(2, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(2)){
    delay(10);
    Serial.print(0);
    while(!digitalRead(2));
    delay(10);
  }
}
