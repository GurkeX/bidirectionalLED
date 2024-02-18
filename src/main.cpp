#include <Arduino.h>

#include <led_comm.h>

long beginning = 0;

// functions to decode and encode Strings to bits and bytes and vice versa
void encodeStringToBinary(const String &message, uint8_t *binaryMessage, size_t maxLength);

void setup()
{
    Serial.begin(9600);
    initLedComm();
}

void loop()
{
    
    //delay(500);
    // setReceivingMode();
    if (Serial.available() > 0) {
        // Read the incoming string from the serial port
        String receivedString = Serial.readStringUntil('\n');
        // Trigger the sendMessage function with the received string
        sendMessage(receivedString);
    
    } else if(checkLight()) {
        // delay(BIT_DURATION + BIT_DURATION / 3);
        // No data on the serial port, check for received bits
        Serial.println(receiveMessage());
        // Bit received, handle accordingly
        // For example, print the received bit to the serial monitor
    } 

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