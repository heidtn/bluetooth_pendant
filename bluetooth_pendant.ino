#include <SoftwareSerial.h>

void signal ();
void blinkLED (int, int, int, int);
void sendChar ();
void buttonPressed();

int led     = 0;
int button  = 2;
int rx      = 3;
int tx      = 4;

boolean led_s = false;
volatile boolean buttonFlag = false;
SoftwareSerial s(rx, tx);

void setup() {
  pinMode(rx, INPUT);
  pinMode(tx, OUTPUT);
  pinMode(led, OUTPUT);

  attachInterrupt(0, inter, FALLING);
  interrupts();
  
  s.begin(9600);
}

void loop() {
  //delay(1000);
  //signal();
  //s.println("H");
  if(s.available() > 0) {
    s.flush();
    signal();
  }
  if (buttonFlag) {
    buttonPressed();
    buttonFlag = false;
  } 
}


void signal() {
  blinkLED(led, 100, 4, 150);
}

void inter () {
  noInterrupts();
  buttonFlag = true;
  interrupts();
}

void buttonPressed () {
  s.println("H");
}


void blinkLED (int ledNum, int blinkDuration, int numCycles, int intensity) {
  // Prime
  analogWrite(ledNum, intensity);
  delay(blinkDuration);
  // Main blink cycle
  for ( int i = 0; i < numCycles - 1; i++) {
    analogWrite(ledNum, 0);
    delay(blinkDuration);
    analogWrite(ledNum, intensity);
    delay(blinkDuration);
  }
  analogWrite(ledNum, 0);
}

void sendChar () {
  s.println("H");
}

