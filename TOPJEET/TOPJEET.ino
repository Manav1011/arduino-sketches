#include "WiFi.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
int resval = 0;  // holds the value
int respin = A0; // sensor pin used
#define WLAN_SSID       "LAVA"
#define WLAN_PASS       "12345678"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "1912nihal"
#define AIO_KEY       "aio_nOSz1772p5fK8mLEijHGrzrKAqyk"
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish Temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/test");
int trig=12;
int echo=14;
int time1=0;
int distance=0;
void MQTT_connect();
void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.println(); Serial.println();
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.print("Connecting to ");
  
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
}
void loop() {
  MQTT_connect();
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  time1=pulseIn(echo,HIGH);
  distance=(time1*0.034)/2;
  if (! Temperature.publish(distance)) {
    Serial.println(F("distance Failed"));
  } else {
    Serial.println(F("distance OK!"));
  }
  if (resval<=100){ Serial.println("distance: Empty"); } 
  else if (resval>100 && resval<=300){ Serial.println("distance : Low"); } else if (resval>300 && resval<=330){ Serial.println("distance Level: Medium"); } 
  else if (resval>330){ 
    Serial.println("distance Level: High"); 
  }
  delay(2000);
}
void MQTT_connect()
{
  int8_t ret;
  if (mqtt.connected())
  {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}