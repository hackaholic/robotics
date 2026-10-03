#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    OLED_RESET
);


// Our RAW I2C command function
void sendCommand(uint8_t command)
{
    Wire.beginTransmission(OLED_ADDR);

    Wire.write(0x00);       // SSD1306: next byte is a command
    Wire.write(command);    // actual command

    Wire.endTransmission();
}

void sendData(uint8_t data)
{
    Wire.beginTransmission(OLED_ADDR);

    Wire.write(0x40);      // SSD1306: next byte is DISPLAY DATA
    Wire.write(data);      // 8 pixel bits

    Wire.endTransmission();
}


void setup()
{
    Wire.begin(D2, D1);  // SDA=D2, SCL=D1

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR))
    {
        while (true)
            delay(100);
    }

    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 20);
    display.println("HELLO");

    display.display();

    //display.setCursor(10, 20);
    for (int i = 0; i < 20; i++)
    {
        sendData(0xFF);   // 11111111
    }
}

void loop()
{
    // RAW I2C command
    sendCommand(0xAE);      // SSD1306 Display OFF
    delay(2000);

    // RAW I2C command
    sendCommand(0xAF);      // SSD1306 Display ON
    delay(2000);
}