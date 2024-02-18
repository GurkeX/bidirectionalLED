#include <led_comm.h>


void initLedComm()
{
    pinMode(KATHODE, INPUT);
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
    pinMode(KATHODE, INPUT);
    //Serial.print("receiving mode\n");
    delay(10);
}

void setSendingMode()
{
    pinMode(KATHODE, OUTPUT);
    analogWrite(KATHODE, HIGH);
    digitalWrite(ANODE, HIGH);
    Serial.print("sending mode\n");
    delay(10);
}

// Sending section

void sendBit(bool bit)
{   
    digitalWrite(KATHODE, bit ? LOW : HIGH); // Set the LED to HIGH for  1, LOW for  0
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

void sendByte(uint8_t byte)
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

bool receiveBit()
{
    switch (analogRead(KATHODE))
    {
    case 0:
        return true;
        break;

    // case 1:
    //     return true;
    //     break;

    // case 2:
    //     return true;
    //     break;   

    // case 3:
    //     return true;
    //     break;     
    
    default:
        return false;
        break;
    }
}

uint8_t receiveByte()
{
    Serial.println("receiveByte");
    
    uint8_t byte = 0;
    for (int i = 0; i < 8; ++i)
    {
        bool bit = receiveBit();
        delay(BIT_DURATION);
        byte |= bit << (7 - i); // Shift the received bit into the correct position
    }
    
    // Serial.println("Byte as 0s and 1s:");
    // for (int i = 7; i >= 0; --i)
    // {
    //     bool bit = (byte >> i) &  0x01;
    //     Serial.print(bit ? '1' : '0');
    // }
    // Serial.println(); // Print a newline after the byte


    //Serial.println(static_cast<char>(byte));

    return byte;
}

String receiveMessage()
{
    setReceivingMode();
    String message = ""; 
        uint8_t byte = receiveByte();
        message += static_cast<char>(byte);
    return message;
}