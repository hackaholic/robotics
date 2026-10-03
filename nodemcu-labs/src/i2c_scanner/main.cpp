#include <Arduino.h>
#include <Wire.h>

void setup()
{
    Serial.begin(115200);

    // NodeMCU:
    // SDA = D2
    // SCL = D1
    Wire.begin(D2, D1);

    Serial.println("\nI2C Scanner");
}

void loop()
{
    for (uint8_t address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);

        uint8_t result = Wire.endTransmission();

        if (result == 0)
        {
            Serial.print("FOUND: 0x");

            if (address < 16)
                Serial.print("0");

            Serial.println(address, HEX);
        }
    }

    Serial.println("Scan complete\n");
    delay(3000);
}