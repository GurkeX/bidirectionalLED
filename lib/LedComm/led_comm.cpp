#include <led_comm.h>


void initLedComm()
{
    pinMode(CATHODE, INPUT);
    pinMode(ANODE, OUTPUT);
}

void sendMessage(const String &message)
{
    setSendingMode();
    for (unsigned int i = 0; i < message.length(); ++i)
    {
        sendByte(static_cast<uint8_t>(message[i]));
    }
}

// Mode switching section

void setReceivingMode()
{
    digitalWrite(ANODE, LOW);
    pinMode(CATHODE, INPUT);
    delay(10);
}

void setSendingMode()
{
    pinMode(CATHODE, OUTPUT);
    analogWrite(CATHODE, HIGH);
    digitalWrite(ANODE, HIGH);
}

// Sending section

void sendBit(bool bit)
{   
    digitalWrite(CATHODE, bit ? LOW : HIGH); // Set the LED to LOW for  1, HIGH for  0
    delay(BIT_DURATION);                     // Wait for the duration of a bit
}

void sendStartBit()
{
    sendBit(START_BIT); // Send a start bit (always  1)
}

void sendStopBit()
{
    sendBit(STOP_BIT); // Send a stop bit (always  0)
}

void sendByte(const uint8_t &byte)
{
    sendStartBit(); // Send the start bit
    for (int i = 7; i >= 0; --i)
    {
        bool bit = (byte >> i) & 0x01;
        sendBit(bit);
    }
    sendStopBit(); // Send the stop bit
}

// Receiving section

bool checkLight() {
    pinMode(CATHODE, OUTPUT);
    digitalWrite(CATHODE, HIGH);
    digitalWrite(ANODE, LOW);

    pinMode(CATHODE, INPUT);

    delay(20);

    switch (digitalRead(CATHODE))
    {
    case 0:
        delay(BIT_DURATION - 20);
        return true;
        break;
    
    default:
        return false;
        break;
    }
}

bool receiveBit()
{
    pinMode(CATHODE, OUTPUT);
    digitalWrite(CATHODE, HIGH);
    digitalWrite(ANODE, LOW);

    pinMode(CATHODE, INPUT);

    delay(20);

    switch (digitalRead(CATHODE))
    {
    case 0:
        delay(BIT_DURATION - 20);
        return true;
        break;
    
    default:
        delay(BIT_DURATION - 20);
        return false;
        break;
    }
}

uint8_t receiveByte()
{
    
    uint8_t byte = 0;
    for (int i = 0; i < 8; ++i)
    {
        bool bit = receiveBit();
        byte |= bit << (7 - i); // Shift the received bit into the correct position
    }

    return byte;
}

String receiveMessage()
{
    unsigned int receiveMessageCalls = 0; // Counter of the calls of receiveMessage without data being received
    String message = ""; 
    while (receiveMessageCalls < 5) // Check if whole data block has been received
    {
        receiveMessageCalls ++;
            if (checkLight()) {
                receiveMessageCalls = 0; // Reset receiveMessageCalls because data has been received
                setReceivingMode();
                uint8_t byte = receiveByte();
                message += static_cast<char>(byte);
            }
    }
    return message;
}
    