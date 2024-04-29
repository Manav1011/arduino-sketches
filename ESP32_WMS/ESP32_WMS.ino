#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define RAIN_GPIO 18
#define FIRE_GPIO 5
#define GAS_GPIO 34

const char *ssid = "Galaxy S21 FE 5G";
const char *password = "sflh2265";
const char *topic_RAIN= "RAIN";
const char *topic_FIRE= "FIRE";
const char *topic_GAS= "GAS";
const char *topic_TEMP = "TEMP";
const char *topic_HUMD = "HUMD";
const char *mqtt_broker = "192.168.115.106";
const char *mqtt_username = "Manav1011";
const char *mqtt_password = "Manav@1011";
const int mqtt_port = 1883;

DHT dht(15,DHT11);
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_broker, mqtt_port);

  while (!client.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password, NULL, 0, false, NULL, true)) {
      Serial.println("Public emqx mqtt broker connected");      
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  pinMode(FIRE_GPIO,INPUT);
  pinMode(RAIN_GPIO,INPUT);
  dht.begin();
  delay(2000);
}

void loop() {  
  float temp = dht.readTemperature();
  float humd = dht.readHumidity();  
  client.publish(topic_TEMP,String(temp).c_str());
  client.publish(topic_HUMD,String(humd).c_str());  
  client.publish(topic_RAIN,String(digitalRead(RAIN_GPIO)).c_str());  
  client.publish(topic_FIRE,String(digitalRead(FIRE_GPIO)).c_str());
  client.publish(topic_GAS,String(analogRead(GAS_GPIO)).c_str());
  delay(1000);
}
