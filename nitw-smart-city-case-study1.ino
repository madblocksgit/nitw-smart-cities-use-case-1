#include <WiFi.h>
#include <ThingSpeak.h>

#define channelId 1650222
#define writeKey "MTPZ8BNZWXQJ1IOZ"
#define readKey "14HCVL6LBTML5WA6"

#define lightSensor 23 //GPIO Pin
#define streetLight LED_BUILTIN

#define darkness 0
#define brightness 1

int lightStatus=0; // off

#define WIFI_SSID "The WiFi"
#define WIFI_PASSWORD "madhus2022"

WiFiClient client; // client object

void setup() { // execute the logic for only one time
  pinMode(lightSensor,INPUT);
  pinMode(streetLight,OUTPUT); // port declaration

  Serial.begin(115200); // monitoring the sensor
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.println("Connecting to Router");
  while(WiFi.status()!=WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("WiFi Connected");
  ThingSpeak.begin(client); // it will connect with thingspeak server
}

void loop() { // infinite loop

  int sensorValue=digitalRead(lightSensor);
  Serial.print("Light Sensor Status: ");
  Serial.println(sensorValue);
  delay(1000); // 1second

  if(sensorValue==darkness) {
    Serial.println("Light: On");
    ThingSpeak.setField(1,10); // light is needed 10>0
  } else if(sensorValue==brightness) {
    Serial.println("Light: Off");
    ThingSpeak.setField(1,0); // no light is needed
  }

  ThingSpeak.setField(2,sensorValue); // 2 - field2
  int statusCode=ThingSpeak.writeFields(channelId,writeKey);
  if(statusCode==200) {
    Serial.println("Data Uploaded to Cloud");
  } else {
    Serial.println("Data not uploaded");
  }
  delay(20000); // 20-seconds
}
