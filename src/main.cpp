#include <Arduino.h>

#include <led_comm.h>

long beginning = 0;

void setup()
{
    Serial.begin(9600);
    initLedComm();
}

void loop()
{
    if (Serial.available() > 0) {
        String receivedString = Serial.readStringUntil('\n');// Read the incoming string from the serial port

        sendMessage(receivedString); // Trigger the sendMessage function with the received string
    }

    String message = receiveMessage(); // Trigger the receiveMessage function

    if (message != "") {
        Serial.println(message);
    }

}