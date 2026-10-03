#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define SD_CS D8

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("\nSPI SD Lab 1");
    Serial.println("Trying to initialize SD card...");

    if (!SD.begin(SD_CS)) {
        Serial.println("SD initialization FAILED");
        return;
    }

    Serial.println("SD initialization SUCCESS");
}

void loop()
{
}