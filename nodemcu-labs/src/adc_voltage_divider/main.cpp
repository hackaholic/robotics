#include <Arduino.h>

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    int adcValue = analogRead(A0);

    Serial.print("ADC = ");
    Serial.println(adcValue);

    delay(1000);
}