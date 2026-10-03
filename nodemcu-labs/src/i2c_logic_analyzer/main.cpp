#include <Arduino.h>
#include <Wire.h>

#define SDA_PIN D2
#define SCL_PIN D1

void setup()
{
    Serial.begin(115200);

    Wire.begin(SDA_PIN, SCL_PIN);

    delay(2000);

    // One tiny I2C transaction to OLED address 0x3C
    Wire.beginTransmission(0x3C);
    Wire.write(0x00);
    Wire.endTransmission();

    Serial.println("I2C transaction sent");
}

void loop()
{
}