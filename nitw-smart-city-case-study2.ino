#include <DHT.h>

DHT dht(2,DHT11);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {

  float humidity=dht.readHumidity();
  float temperature=dht.readTemperature();

  // null values
  if(isnan(humidity) || isnan(temperature))
    return;

  Serial.print("Humidity: "); 
  Serial.print(humidity);
  Serial.print(", Temperature: ");
  Serial.println(temperature);

  delay(1000);
  

}
