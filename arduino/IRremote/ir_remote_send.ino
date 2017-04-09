#include<IRremote.h>

IRsend irsend;

char c;

void setup(){
  Serial.begin(9600);
}

void loop(){
  c = Serial.read();
  Serial.println(c);
  if(c == '0'){
    irsend.sendRC6(0xC00010, 24);
    delay(2000);
  }
}

