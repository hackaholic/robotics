
// Author: Kumar Shubham

#include<ESP8266WiFi.h>

void setup()
{
  // begin serial at baud rate 115200
  Serial.begin(115200);
  Serial.flush();
  Serial.println();

  // initialize the mode of esp8266 to station mode
  WiFi.mode(WIFI_STA);   
  WiFi.disconnect();
  delay(100);
}

void loop()
{
  Serial.print("Scan start ... ");
  // starting wifi scan
  int n = WiFi.scanNetworks();
  if( n > 0 ) {
    Serial.print(n);
    Serial.println(" network(s) found");
    for (int i = 0; i < n; i++)
    {
      Serial.print(WiFi.SSID(i) + ", Signal Strength: ");
      /*
         RSSI -> Received Signal Strength Indicator
         ranges from absolute  -100(lowest) to 0 (strongest)
         it’s always negative, indicating how much signal strength has been lost. 
         lower the value stronger the signal strength
       */
      Serial.print(WiFi.RSSI(i));

      // get encryption type of the wifi network
      // TKIP (WPA) = 2 WEP = 5 CCMP (WPA) = 4 NONE = 7 AUTO = 8
      int encryption = WiFi.encryptionType(i);
      Serial.print(", Encryption Type:");
      Serial.println(encryption);
    }
    Serial.println();
  }
  else {
    Serial.println("No network Found");
  }
  delay(5000);
}
