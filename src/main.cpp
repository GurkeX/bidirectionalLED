#include <Arduino.h>


#define KATHODE A0 // kathode of the led
#define ANODE 13 // anode of the led

#define START_BIT  0 // Start bit is always  0
#define STOP_BIT  1 // Stop bit is always  1
#define BIT_DURATION  100 // Duration of one bit in milliseconds


// functions to decode and encode Strings to bits and bytes and vice versa
uint8_t readMessage();
void sendMessage(const String& message);
void encodeStringToBinary(const String& message, uint8_t* binaryMessage, size_t maxLength);

// functions to send and recieve bits from and to the other Arduino
void sendBit(bool bit);
void sendStartBit();
void sendStopBit();
void sendByte(uint8_t byte);

void setup() {

  Serial.begin(9600);
  pinMode(KATHODE, INPUT);
  pinMode(ANODE, OUTPUT);
  // pinMode(KATHODE, OUTPUT);
  // digitalWrite(KATHODE, LOW);
  //digitalWrite(ANODE, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  pinMode(KATHODE, INPUT);
  digitalWrite(ANODE, LOW);
  delay(500);
  Serial.print(analogRead(KATHODE));
  Serial.print("\n");
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
  pinMode(KATHODE, OUTPUT);
  analogWrite(KATHODE, LOW);
  digitalWrite(ANODE, HIGH);
  Serial.print("light output\n");
  // delay(500);

  for (unsigned int i =  0; i < message.length(); ++i) {
    sendByte(static_cast<uint8_t>(message[i]));
  }

  
  // uint8_t binaryMessage[256];
  // encodeStringToBinary(message, binaryMessage, sizeof(binaryMessage));

  // for (size_t i =  0; i < sizeof(binaryMessage); ++i) {
  //   for (int j =  7; j >=  0; --j) {
  //     Serial.print((binaryMessage[i] >> j) &  0x01 ? '1' : '0');
  //   }
  //   Serial.print(' '); // Optional space between bytes
  // }
  // Serial.println(); // Newline at the end
}

uint8_t readMessage() {
  return 0;
}

void sendBit(bool bit) {
  digitalWrite(KATHODE, bit ? HIGH : LOW); // Set the LED to HIGH for  1, LOW for  0
  delay(BIT_DURATION); // Wait for the duration of a bit
}

void sendStartBit() {
  sendBit(START_BIT); // Send a start bit (always  0)
}

void sendStopBit() {
  sendBit(STOP_BIT); // Send a stop bit (always  1)
}

void sendByte(uint8_t byte) {
  sendStartBit(); // Send the start bit
  for (int i =  7; i >=  0; --i) {
    bool bit = (byte >> i) &  0x01;
    sendBit(bit);
  }
  sendStopBit(); // Send the stop bit
}
