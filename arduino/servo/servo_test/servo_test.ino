#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos;    // variable to store the servo position
char my_buffer[3];

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}


void my_flush(){
  int i;
  for(i=0;i<3;i++)
    my_buffer[i]='\0';
}

void loop() {
  
  if(Serial.available() >0){
    my_flush();
    Serial.readBytes(my_buffer, 3);
    pos = atoi(my_buffer);
    Serial.println(pos);
    myservo.write(pos);
  }
}
