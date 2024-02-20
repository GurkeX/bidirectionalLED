#include <Arduino.h>

#define CATHODE 13 // kathode of the led
#define ANODE 12   // anode of the led

#define START_BIT 1      // Start bit is always  1
#define STOP_BIT 0       // Stop bit is always  0
#define BIT_DURATION 20 // Duration of one bit in milliseconds
#define LED_DISCHARGE_TIME_MS 5 // Time in milliseconds it takes for the led to discharge when light shines on it 


void initLedComm(); 

// functions to send and recieve bits from and to the other Arduino
void sendBit(bool bit);
void sendStartBit();
void sendStopBit();
void sendByte(const uint8_t &byte);

// bool receiveBit(bool isData);
bool receiveBit();
bool checkLight();
uint8_t receiveByte();

String receiveMessage();
void sendMessage(const String &message);

// functions to set recieving or sending mode of Arduino
void setReceivingMode();
void setSendingMode();