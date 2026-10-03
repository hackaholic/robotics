#include <Arduino.h>

#define BUTTON_PIN D7

void setup() {
    Serial.begin(115200);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    Serial.println();
    Serial.println("GPIO Input Lab");
}

void loop() {

    int state = digitalRead(BUTTON_PIN);

    if (state == LOW) {
        Serial.println("BUTTON PRESSED  -> LOW");
    } else {
        Serial.println("BUTTON RELEASED -> HIGH");
    }

    delay(500);
}