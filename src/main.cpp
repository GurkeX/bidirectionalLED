#include <Arduino.h>

#define kathode 12
#define anode 13


// put function declarations here:
int readLED();

void setup() {
  // put your setup code here, to run once:
  readLED();

  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(anode, OUTPUT);
  pinMode(kathode, OUTPUT);
  digitalWrite(kathode, LOW);
  //digitalWrite(anode, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  pinMode(A0, INPUT);
  digitalWrite(anode, LOW);
  delay(500);
  Serial.print(analogRead(A0));
  delay(500);

  pinMode(A0, OUTPUT);
  analogWrite(A0, LOW);
  digitalWrite(anode, HIGH);
  Serial.print(" led an\n");
  delay(500);
  

}

// Function to encode string message recieved via serial into 8bit message, that can be sent using 0s and 1s

// put function definitions here:
int readLED() {
  return 0;
}