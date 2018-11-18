/*
 * ESP8266 NodeMCU LED Control over WiFi Demo
 *
 * https://circuits4you.com
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include<PubSubClient.h>
 
#define ledPin D4

void callback(char* topic, byte* payload, unsigned int length1);

//SSID and Password of your WiFi router
//const char* ssid = "Ananthaya";
//const char* password = "GJTM9RY9TY4"; 
const char* ssid = "AndroidAP";
const char* password = "lrkr9222"; 
 
const char* mqtt_server = "test.mosquitto.org";
WiFiClient WiFiclient;
PubSubClient client(mqtt_server, 1883, callback, WiFiclient);
 
void setup() {
 pinMode(ledPin, OUTPUT);
 Serial.begin(9600);
 delay(10);
 Serial.println();
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
 
 Serial.println("");
 Serial.println("WiFi connected");  
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
 delay(2000);
 
 reconnect();
}

void callback(char* topic, byte* payload, unsigned int length1)
{
  Serial.print("Message Arrived [");
  Serial.print(topic);
  Serial.println("]");
  for(int i=0; i<length1; i++)
  {
    Serial.print((char)payload[i]);
  }

  if((char)payload[0]=='1') {
    //Serial.print((char)payload[0]);
    digitalWrite(ledPin, LOW);
   }
   
  if((char)payload[0]== '0'){ 
    //Serial.print((char)payload[0]);
    digitalWrite(ledPin, HIGH);
  }
  Serial.println();
}

void reconnect()
{
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  while(!client.connected())
  {
    if(client.connect("clientId-nKuo9cZmB5"))
    {
      Serial.println("Connected...");
      client.subscribe("ledcontrol");
    }else
    {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(500);
    }
  }
}

void loop()
{
  if(!client.connected()){
      reconnect();
    }
    
    client.loop();
}
