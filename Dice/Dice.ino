const int
IP_SWI = 2,
A = 4,
B = 5,
C = 6,
D = 7,
E = 8,
F = 9,
G = 10,
H = 11;

int num;

void setup() {
  pinMode(IP_SWI, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  for (int i = A; i <= H; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = A; i <= H; i++) {
    digitalWrite(i, HIGH);
  }

  Serial.begin(9600);
  randomSeed(analogRead(A0));
}

void loop() {
  while (!digitalRead(IP_SWI));
  digitalWrite(13, LOW);
  if (!digitalRead(IP_SWI)) {
    digitalWrite(13, HIGH);
    for (int i = 32; i <= 200; i += 8) {
      num = random(6) + 1;
      switch (num) {
        case 1: Set1(); break;
        case 2: Set2(); break;
        case 3: Set3(); break;
        case 4: Set4(); break;
        case 5: Set5(); break;
        case 6: Set6(); break;
      }
      Serial.println(num);
      delay(i);
    }
  }

}

void Set1() {
  for (int i = A; i <= H; i++) {
    switch (i) {
      case B:
      case C: digitalWrite(i, HIGH);
        break;
      default: digitalWrite(i, LOW);
    }
  }
}


void Set2() {
  for (int i = A; i <= H; i++) {
    switch (i) {
      case H:
      case G:
      case C: digitalWrite(i, LOW);
        break;
      default: digitalWrite(i, HIGH);
    }
  }
}

void Set3() {
  for (int i = A; i <= H; i++) {
    switch (i) {
      case E:
      case G:
      case H: digitalWrite(i, LOW);
        break;
      default: digitalWrite(i, HIGH);
    }
  }
}

void Set4() {
  for (int i = A; i <= H; i++) {
    switch (i) {
      case F:
      case G:
      case B:
      case C: digitalWrite(i, HIGH);
        break;
      default: digitalWrite(i, LOW);
    }
  }
}

void Set5() {
  for (int i = A; i <= H; i++) {
    switch (i) {
      case H:
      case B:
      case E: digitalWrite(i, LOW);
        break;
      default: digitalWrite(i, HIGH);
    }
  }
}

void Set6() {
  for (int i = A; i <= H; i++) {
    switch (i) {
      case B:
      case H: digitalWrite(i, LOW);
        break;
      default: digitalWrite(i, HIGH);
    }
  }
}

