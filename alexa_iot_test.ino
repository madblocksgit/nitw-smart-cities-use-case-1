#include <WiFi.h>
#include <ThingSpeak.h>

WiFiClient client;

#define WIFI_SSID "The WiFi"
#define WIFI_PASSWORD "madhus2022"

#define lampPin 23
#define channelNumber 1630130

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  while(WiFi.status()!=WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("WIFI Connected");
  ThingSpeak.begin(client);
  pinMode(lampPin,OUTPUT);
}

void loop() {
  int lampStatus = ThingSpeak.readIntField(channelNumber,1);  
  int statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    Serial.println("Lamp Status: " + String(lampStatus));
  }
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }
  delay(15000);
}
