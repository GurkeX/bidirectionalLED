#include <Arduino.h>


#define KATHODE A0 // kathode of the led
#define ANODE 13 // anode of the led

#define START_BIT  0 // Start bit is always  0
#define STOP_BIT  1 // Stop bit is always  1
#define BIT_DURATION  100 // Duration of one bit in milliseconds


// functions to decode and encode Strings to bits and bytes and vice versa
void reveiveMessage();
void sendMessage(const String& message);
void encodeStringToBinary(const String& message, uint8_t* binaryMessage, size_t maxLength);

// functions to send and recieve bits from and to the other Arduino
void sendBit(bool bit);
void sendStartBit();
void sendStopBit();
void sendByte(uint8_t byte);

bool receiveBit();
uint8_t receiveByte();

// functions to set recieving or sending mode of Arduino
void setReceivingMode();
void setSendingMode();


void setup() {

  Serial.begin(9600);
  pinMode(KATHODE, INPUT);
  pinMode(ANODE, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
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
  setSendingMode();
  
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

// Mode switching section

void setReceivingMode() {
  pinMode(KATHODE, INPUT);
  digitalWrite(ANODE, LOW);
  Serial.print("receiving mode\n");
  delay(10);
}
void setSendingMode() {
  pinMode(KATHODE, OUTPUT);
  analogWrite(KATHODE, LOW);
  digitalWrite(ANODE, HIGH);
  Serial.print("sending mode\n");
  delay(10);
}

// Sending section

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


// Receiving section 


bool receiveBit() {
  delay(BIT_DURATION); // Wait for the duration of a bit
  return analogRead(KATHODE) == HIGH; // Return true if the LED is HIGH, false otherwise
}

uint8_t receiveByte() {
  while (!receiveBit()); // Wait until the start bit is received
  uint8_t byte =  0;
  for (int i =  0; i <  8; ++i) {
    byte |= receiveBit() << i; // Shift the received bit into the correct position
  }
  if (!receiveBit()) { // Check for the stop bit
    // Handle error: stop bit was not received
  }
  return byte;
}

void receiveMessage() {
  setReceivingMode();
  String message = "";
  while (true) { // Loop until a stop condition is detected
    uint8_t byte = receiveByte();
    message += static_cast<char>(byte);
    // Check for a stop condition (e.g., a specific sequence of bytes)
  }
}