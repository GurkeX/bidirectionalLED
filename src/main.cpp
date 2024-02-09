#include <Arduino.h>

#include <led_comm.h>

// functions to decode and encode Strings to bits and bytes and vice versa
void encodeStringToBinary(const String &message, uint8_t *binaryMessage, size_t maxLength);

void setup()
{

    Serial.begin(9600);
    initLedComm();
}

void loop()
{
    // put your main code here, to run repeatedly:
    setReceivingMode();
    Serial.print(analogRead(KATHODE));
    Serial.print("\n");
    delay(500);

    String teststring = "Hello";

    sendMessage(teststring);

    delay(500);
}

// Function to encode string message recieved via serial into 8bit message, that can be sent using 0s and 1s
void encodeStringToBinary(const String &message, uint8_t *binaryMessage, size_t maxLength)
{
    size_t length = min(message.length(), maxLength);
    for (size_t i = 0; i < length; ++i)
    {
        binaryMessage[i] = static_cast<uint8_t>(message[i]);
    }
}