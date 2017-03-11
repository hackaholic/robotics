#include <SoftwareSerial.h>

#define TxD 2

#define RxD 3

SoftwareSerial mySerial(TxD, RxD); // Tx, Rx for Bluetooth

char my_buffer[32];

void setup() {

mySerial.begin(9600); // For Bluetooth

Serial.begin(9600); // For the IDE monitor Tools -> Serial Monitor
pinMode(13, OUTPUT);
resetBuffer();

// Any code that you want to run once....

}

void resetBuffer(){
  int i;
  for(i=0;i<32;i++){
    my_buffer[i++]='\0';
    }
  }

void loop() {
boolean isValidInput; do { byte c; // get the next character from the bluetooth serial port

while(!mySerial.available());
 c = mySerial.read(); // Execute the option based on the character recieved
 Serial.println(c);

  if(c == 49){
    digitalWrite(13, HIGH);
    }
  if(c == 48){
    digitalWrite(13, LOW);
    }
 } while ( isValidInput == true ); // Repeat the loop
}
