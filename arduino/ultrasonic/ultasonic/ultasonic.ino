#include <NewPing.h>

// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 1000 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define BLIN_PIN 13   // Led pin

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  beep(50);
  beep(50);
  beep(50);
}

void beep(int delayms){
  digitalWrite(8, HIGH);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  digitalWrite(8, LOW);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms   
}  

void loop() {
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  int distance_in_cm = uS / US_ROUNDTRIP_CM; //Convert ping time to distance
  Serial.print(distance_in_cm);// print result (0 = outside set distance range, no ping echo)
  if(distance_in_cm <=90){
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage
  }
  else
      digitalWrite(13, LOW);
  Serial.println("cm");
}
