#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#define GAS_GPIO 36

const char *ssid = "Manav Shah 4G";
const char *password = "9925717005ms";
const char *topic = "testTopic";
const char *topic_DH11 = "DH11";
const char *mqtt_broker = "192.168.29.18";
const char *mqtt_username = "Manav1011";
const char *mqtt_password = "Manav@1011";
const int mqtt_port = 1883;

DHT dht(15,DHT11);


WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Hello");
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
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Public emqx mqtt broker connected");
      client.publish(topic, "Hi EMQX I'm ESP32 ^^");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  dht.begin();
  delay(2000);
}

void loop() {
  client.loop();
  float temp = dht.readTemperature();
  float humd = dht.readHumidity();
  String jsonString = "{\"Temperature\":\"" + String(temp) + "\",\"Humidity\":\"" + String(humd) + "\"}";
  client.publish(topic_DH11, jsonString.c_str());
  Serial.println(analogRead(GAS_GPIO));
  delay(1000);
}
