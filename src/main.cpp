#include <Arduino.h>

#define kathode 12
#define anode 13


// put function declarations here:
int readLED();

void setup() {
  // put your setup code here, to run once:
  readLED();

  pinMode(anode, OUTPUT);
  digitalWrite(anode, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int readLED() {
  return 0;
}