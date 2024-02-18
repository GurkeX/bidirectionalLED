#include <Arduino.h>

#define KATHODE A0 // kathode of the led
#define ANODE 13   // anode of the led

#define START_BIT 1      // Start bit is always  1
#define STOP_BIT 0       // Stop bit is always  0
#define BIT_DURATION 200 // Duration of one bit in milliseconds
#define LED_ON_VALUE 70 // Value of the analog read when light is shone on it

void initLedComm();

// functions to send and recieve bits from and to the other Arduino
void sendBit(bool bit);
void sendStartBit();
void sendStopBit();
void sendByte(uint8_t byte);

// bool receiveBit(bool isData);
bool receiveBit();
uint8_t receiveByte();

String receiveMessage();
void sendMessage(const String &message);

// functions to set recieving or sending mode of Arduino
void setReceivingMode();
void setSendingMode();