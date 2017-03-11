#include<SoftwareSerial.h>

#define TxD 2
#define RxD 3

SoftwareSerial bluetoothSerial(TxD, RxD);

char c;

void setup() {
  bluetoothSerial.begin(9600);
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  if(bluetoothSerial.available()){
    c = bluetoothSerial.read();
    Serial.println(c);
    if(c=='a'){
      Serial.println("Hello");
    }
  }
  // put your main code here, to run repeatedly:

}
