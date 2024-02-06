#include <Arduino.h>


#define kathode 12
#define anode 13


// put function declarations here:
uint8_t readMessage();
void sendMessage(const String& message);
void encodeStringToBinary(const String& message, uint8_t* binaryMessage, size_t maxLength);

void setup() {

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

  String teststring = "Hello";

  sendMessage(teststring);

  delay(500);

}

// Function to encode string message recieved via serial into 8bit message, that can be sent using 0s and 1s
void encodeStringToBinary(const String& message, uint8_t* binaryMessage, size_t maxLength) {
  size_t length = min(message.length(), maxLength);
  for (size_t i =  0; i < length; ++i) {
    binaryMessage[i] = static_cast<uint8_t>(message[i]);
  }
}

void sendMessage(const String& message) 
{
  uint8_t binaryMessage[4];
  encodeStringToBinary(message, binaryMessage, sizeof(binaryMessage));

  for (size_t i =  0; i < sizeof(binaryMessage); ++i) {
    for (int j =  7; j >=  0; --j) {
      Serial.print((binaryMessage[i] >> j) &  0x01 ? '1' : '0');
    }
    Serial.print(' '); // Optional space between bytes
  }
  Serial.println(); // Newline at the end
}

uint8_t readMessage() {
  return 0;
}