
int pin = 5;
int val = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  val = digitalRead(pin);
  if(val == 0){
    Serial.println("black surface detected");
  }
  else {
    Serial.println("White surce detected");
    }
  Serial.println(val);
  delay(1000);

}