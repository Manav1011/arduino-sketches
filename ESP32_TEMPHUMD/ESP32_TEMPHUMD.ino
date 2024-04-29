#include<DHT.h>

DHT dht(25,DHT11);

void setup() {
  dht.begin();
  delay(2000);
  Serial.begin(115200);
}

void loop(){
  float temp = dht.readTemperature();
  float humd = dht.readHumidity();
  String jsonString = "{\"Temperature\":\"" + String(temp) + "\",\"Humidity\":\"" + String(humd) + "\"}";
  Serial.println(jsonString);
  delay(1000);
}