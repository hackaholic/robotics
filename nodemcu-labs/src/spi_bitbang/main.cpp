#include <Arduino.h>

#define CS    D8
#define SCK   D5
#define MOSI  D7
#define MISO  D6

#define WASTE 1000


// Send ONE bit on MOSI
// and simultaneously receive ONE bit from MISO
int sendBit(int bit)
{
    // 1. Present our outgoing bit on MOSI
    digitalWrite(MOSI, bit ? HIGH : LOW);

    Serial.print("MOSI = ");
    Serial.println(bit);

    delay(WASTE);


    // 2. Rising clock edge
    // Nano samples MOSI here
    digitalWrite(SCK, HIGH);

    Serial.println("SCK = HIGH  <-- BOTH SAMPLE NOW");


    // ESP samples Nano's MISO
    int receivedBit = digitalRead(MISO);

    Serial.print("MISO = ");
    Serial.println(receivedBit);

    delay(WASTE);


    // 3. Finish this clock cycle
    digitalWrite(SCK, LOW);

    Serial.println("SCK = LOW");

    delay(WASTE);

    Serial.println();

    return receivedBit;
}


// Transfer one complete byte
//
// outgoing = byte ESP sends
// return   = byte ESP receives
uint8_t transferByte(uint8_t outgoing)
{
    uint8_t incoming = 0;

    for (int i = 7; i >= 0; i--)
    {
        // Extract one bit from outgoing byte
        int outBit = (outgoing >> i) & 1;

        // Send that bit and receive Nano's bit
        int inBit = sendBit(outBit);

        // Shift previous received bits left
        // and insert the new bit
        incoming = (incoming << 1) | inBit;
    }

    return incoming;
}


void setup()
{
    Serial.begin(115200);

    pinMode(CS, OUTPUT);
    pinMode(SCK, OUTPUT);
    pinMode(MOSI, OUTPUT);

    // Nano drives this pin
    pinMode(MISO, INPUT);


    // SPI idle state
    digitalWrite(CS, HIGH);
    digitalWrite(SCK, LOW);
    digitalWrite(MOSI, LOW);

    delay(WASTE);
}


void loop()
{
    Serial.println("===== START TRANSACTION =====");


    // Select Nano
    digitalWrite(CS, LOW);

    Serial.println("CS = LOW (Nano selected)");
    Serial.println();


    // ESP sends 0xB2
    // Nano should simultaneously send 0x55

    uint8_t received = transferByte(0xB2);


    // Transaction finished
    digitalWrite(CS, HIGH);

    Serial.println("CS = HIGH (transaction finished)");
    Serial.println();


    Serial.println("----- RESULT -----");

    Serial.println("ESP sent:     0xB2");

    Serial.print("ESP received: 0x");
    if (received < 0x10)
        Serial.print("0");

    Serial.println(received, HEX);

    Serial.println("------------------");
    Serial.println();


    delay(5000);
}