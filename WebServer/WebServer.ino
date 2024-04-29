#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define RAIN_GPIO 18
#define FIRE_GPIO 5
#define GAS_GPIO 34

const char *ssid = "Galaxy S21 FE 5G";
const char *password = "sflh2265";
const char *topic_SENSOR_DATA = "SENSOR_DATA";
const char *mqtt_broker = "192.168.115.106";
const char *mqtt_username = "Manav1011";
const char *mqtt_password = "Manav@1011";
const int mqtt_port = 1883;

DHT dht(15, DHT11);
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
  pinMode(FIRE_GPIO, INPUT);
  pinMode(RAIN_GPIO, INPUT);
  pinMode(GAS_GPIO, INPUT);
  dht.begin();
  delay(2000);
}

void loop() {
  float temp = dht.readTemperature();
  float humd = dht.readHumidity();
  int rain = digitalRead(RAIN_GPIO);
  int fire = digitalRead(FIRE_GPIO);
  int gas = digitalRead(GAS_GPIO);
  String jsonString = "{\"temp\":" + String(temp) + ",\"humd\":" + String(humd) + ",\"rain\":" + String(rain) + ",\"fire\":" + String(fire) + ",\"gas\":" + String(gas) + "}";
  client.publish(topic_SENSOR_DATA,jsonString.c_str());
  delay(1000);
}