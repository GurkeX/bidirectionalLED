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
    //setSendingMode();
    
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

bool receiveBit(bool isData)
{
    setReceivingMode();
    int brightness = analogRead(KATHODE);
    //Serial.println(brightness); 
    if (brightness < 100)
    {
        delay(BIT_DURATION); // Wait for the duration of a bit
        return true; // Received
    }

    if(isData) {
        delay(BIT_DURATION); // Wait for the duration
    }
    return false; // Not recieved
}

uint8_t receiveByte()
{
    Serial.println("receiveByte");
    // while (receiveBit())
    //     ; // Wait until the start bit is received
    
    uint8_t byte = 0;
    for (int i = 8; i > 0; --i)
    {
        bool bit = receiveBit(true);
        Serial.println(bit);
        byte |= bit << (i - 1); // Shift the received bit into the correct position
    }
    //Serial.println(millis() - beginning);
    Serial.println("Byte as 0s and 1s:");
    for (int i = 8; i > 0; --i)
    {
        bool bit = (byte >> i) &  0x01;
        Serial.print(bit ? '1' : '0');
    }
    Serial.println(); // Print a newline after the byte


    //Serial.println(static_cast<char>(byte));

    return byte;
}

String receiveMessage()
{
    setReceivingMode();
    //Serial.println("receiving message");
    String message = "";
    //while (receiveBit(true))
    //{ // Loop until a stop condition is detected
        uint8_t byte = receiveByte();
        message += static_cast<char>(byte);
        // Check for a stop condition (e.g., a specific sequence of bytes)
    //}
    return message;
}