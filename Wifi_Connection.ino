/**
 * This establishes the WiFi connection in NodeMCU
 * Sagara Sumathipala
 * 20/09/2020
*/

#include <ESP8266WiFi.h>

const char *ssid =  "******";     // replace with your wifi ssid and wpa2 key
const char *pass =  "******";

WiFiClient client;
 
void setup() 
{
       Serial.begin(9600);
       delay(10);
               
       Serial.print("Connecting to ");
       Serial.println(ssid); 
 
       WiFi.begin(ssid, pass); 
       while (WiFi.status() != WL_CONNECTED) 
       {
            delay(500);
            Serial.print(".");
       }
      Serial.println("");
      Serial.println("WiFi connected"); 
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
}

void loop() 
{      
  
}
