/*
    Author: Kumar Shubham
*/

void setup() {
    Serial.begin(9600);
    Serial.flush();
}

void loop() {
    delay(5000);
    Serial.println("hello");
}