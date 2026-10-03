#include <Arduino.h>

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Serial.println("HELLO FROM UART");
    delay(1000);
}