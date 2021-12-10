#define WRITE_API_KEY "ThinkspeakWriteApi"
#define READ_API_KEY "ThinkspeakReadApi"
#define WIFI_SSID "#######"
#define WIFI_PASS "$$$$$$$"
#define CHANNEL_ID ThinkspeakChannelId
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

WiFiClient  client;

int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0
int sensorValue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(WIFI_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(WIFI_SSID, WIFI_PASS);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  sensorValue = analogRead(analogInPin);
  // print the readings in the Serial Monitor
  Serial.print("sensor = ");
  Serial.println(sensorValue);
  delay(1000);
  // set the fields with the values
  ThingSpeak.setField(1, sensorValue);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(CHANNEL_ID, WRITE_API_KEY);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  delay(5000);
}
