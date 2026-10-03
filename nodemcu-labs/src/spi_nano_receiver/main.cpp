#include <Arduino.h>
#include <SPI.h>

volatile byte receivedByte = 0;
volatile bool byteReceived = false;

// Interrupt Service Routine.
// When SPI hardware reports a completed transfer, execute this function
ISR(SPI_STC_vect)
{
    // SPI hardware has completed receiving 8 bits.
    receivedByte = SPDR;
    byteReceived = true;

    // SPDR = SPI Data Register.
}

void setup()
{
    Serial.begin(115200);

    pinMode(MOSI, INPUT);
    pinMode(SCK, INPUT);
    pinMode(SS, INPUT);
    pinMode(MISO, OUTPUT);

    SPCR |= _BV(SPE);       // SPI enable
    SPCR |= _BV(SPIE);      // SPI interrupt enable
    SPCR &= ~_BV(MSTR);     // peripheral/slave mode explicitly

    SPDR = 0x55;            // byte Nano will shift OUT on MISO

    Serial.println("Nano SPI peripheral ready");
}

void loop()
{
    if (byteReceived)
    {
        byte value;

        noInterrupts();
        value = receivedByte;
        byteReceived = false;
        interrupts();

        Serial.print("Received: 0b");

        for (int i = 7; i >= 0; i--)
            Serial.print((value >> i) & 1);

        Serial.print("  HEX: 0x");
        Serial.println(value, HEX);
    }
}


