#include <Arduino.h>

#define KATHODE A0 // kathode of the led
#define ANODE 13 // anode of the led

#define START_BIT  0 // Start bit is always  0
#define STOP_BIT  1 // Stop bit is always  1
#define BIT_DURATION  100 // Duration of one bit in milliseconds

void initLedComm();

// functions to send and recieve bits from and to the other Arduino
void sendBit(bool bit);
void sendStartBit();
void sendStopBit();
void sendByte(uint8_t byte);

bool receiveBit();
uint8_t receiveByte();

void reveiveMessage();
void sendMessage(const String& message);

// functions to set recieving or sending mode of Arduino
void setReceivingMode();
void setSendingMode();