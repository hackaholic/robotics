#include <Arduino.h>

#define TEST_PIN D1

void setup()
{
    Serial.begin(115200);

    pinMode(TEST_PIN, OUTPUT);
    digitalWrite(TEST_PIN, LOW);

    Serial.println("Logic analyzer basic lab");
    Serial.println("D1: 1 Hz, 50% duty cycle");
}

void loop()
{
    digitalWrite(TEST_PIN, HIGH);
    delay(10);

    digitalWrite(TEST_PIN, LOW);
    delay(10);
}