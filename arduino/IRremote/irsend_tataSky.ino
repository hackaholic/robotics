#include<IRremote.h>
#include<SoftwareSerial.h>

#define TxD 6
#define RxD 7

IRsend irsend;

SoftwareSerial bluetoothSerial(TxD, RxD);

char mybuffer[10];

void setup() {
  bluetoothSerial.begin(9600);
  Serial.begin(9600);
  Serial.setTimeout(10);
}

void flushBuffer() {
  int i;
  for(i=0;i<10;i++){
    mybuffer[i]='\0';
  }
}

void loop() {
if(bluetoothSerial.available()){
  flushBuffer();
  bluetoothSerial.readBytes(mybuffer, 10);
  Serial.println(mybuffer);
  if(strcmp(mybuffer, "right")==0) {
    irsend.sendRC6(0xC0005B, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "help")==0) {
    irsend.sendRC6(0xC00081, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "mute")==0) {
    irsend.sendRC6(0xC0000D, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "back")==0) {
    irsend.sendRC6(0xC00083, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "yellow")==0) {
    irsend.sendRC6(0xC0006F, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "down")==0) {
    irsend.sendRC6(0xC00059, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "home")==0) {
    irsend.sendRC6(0xC00084, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "organizer")==0) {
    irsend.sendRC6(0xC0007E, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "select")==0) {
    irsend.sendRC6(0xC0005C, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "showcase")==0) {
    irsend.sendRC6(0xC0007D, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "tv")==0) {
    irsend.sendRC6(0xC00080, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "black")==0) {
    irsend.sendRC6(0xC00070, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "1")==0) {
    irsend.sendRC6(0xC00001, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "0")==0) {
    irsend.sendRC6(0xC00000, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "3")==0) {
    irsend.sendRC6(0xC00003, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "2")==0) {
    irsend.sendRC6(0xC00002, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "5")==0) {
    irsend.sendRC6(0xC00005, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "4")==0) {
    irsend.sendRC6(0xC00004, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "7")==0) {
    irsend.sendRC6(0xC00007, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "ch_down")==0) {
    irsend.sendRC6(0xC00021, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "9")==0) {
    irsend.sendRC6(0xC00009, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "8")==0) {
    irsend.sendRC6(0xC00008, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "red")==0) {
    irsend.sendRC6(0xC0006D, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "6")==0) {
    irsend.sendRC6(0xC00006, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "fav")==0) {
    irsend.sendRC6(0xC0003C, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "ch_up")==0) {
    irsend.sendRC6(0xC00020, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "active")==0) {
    irsend.sendRC6(0xC000F5, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "vol_up")==0) {
    irsend.sendRC6(0xC00010, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "vol_down")==0) {
    irsend.sendRC6(0xC00011, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "on")==0) {
    irsend.sendRC6(0xC0000C, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "i")==0) {
    irsend.sendRC6(0xC000CB, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "up")==0) {
    irsend.sendRC6(0xC00058, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "green")==0) {
    irsend.sendRC6(0xC0006E, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "guide")==0) {
    irsend.sendRC6(0xC000CC, 24);
    delay(1000);
  }

  if(strcmp(mybuffer, "left")==0) {
    irsend.sendRC6(0xC0005A, 24);
    delay(1000);
  }
  if(strcmp(mybuffer, "pwd_fd")==0) {
    irsend.sendNEC(0x1FE50AF, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "tre+")==0) {
    irsend.sendNEC(0x1FE10EF, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "bass-")==0) {
    irsend.sendNEC(0x1FE8877, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "tre-")==0) {
    irsend.sendNEC(0x1FE906F, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "down_tv")==0) {
    irsend.sendNEC(0xFEB04F, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "right_tv")==0) {
    irsend.sendNEC(0xFE708F, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "vol_fd-")==0) {
    irsend.sendNEC(0x1FEC03F, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "left_tv")==0) {
    irsend.sendNEC(0xFEF00F, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "bass+")==0) {
    irsend.sendNEC(0x1FEC837, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "mute_fd")==0) {
    irsend.sendNEC(0x1FE30CF, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "s_tv")==0) {
    irsend.sendNEC(0xFE48B7, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "vol_tv-")==0) {
    irsend.sendNEC(0xFE58A7, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "up_tv")==0) {
    irsend.sendNEC(0xFE30CF, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "vol_fd+")==0) {
    irsend.sendNEC(0x1FE40BF, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "vol_tv+")==0) {
    irsend.sendNEC(0xFED827, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "pwd_tv")==0) {
    irsend.sendNEC(0xFEA857, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "b_fd")==0) {
    irsend.sendNEC(0x1FEB847, 32);
    delay(1000);
  }
  if(strcmp(mybuffer, "s_fd")==0) {
    irsend.sendNEC(0x1FE38C7, 32);
    delay(1000);
  }
 }
}
