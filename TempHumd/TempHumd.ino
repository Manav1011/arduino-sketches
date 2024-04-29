#include <DHT11.h>

DHT11 dht11(2);

void setup() {  
    Serial.begin(9600);
    dht11.setDelay(1000);
}

void loop() {
    int temperature = 0;
    int humidity = 0;
    int result = dht11.readTemperatureHumidity(temperature, humidity);
    if (result == 0) {
        // Convert integers to strings for concatenation
        String tempString = String(temperature);
        String humidityString = String(humidity);
        
        // Use double quotes for JSON keys and values
        String jsonString = "{\"Temperature\":\"" + tempString + "\",\"Humidity\":\"" + humidityString + "\"}";
        
        Serial.println(jsonString);
    } else {
        Serial.println(DHT11::getErrorString(result));
    }
}
