#include <BluetoothSerial.h>

#define GAS_GPIO 34

BluetoothSerial SerialBT;
void setup() {  
  SerialBT.begin("ESP32_BT");
  pinMode(GAS_GPIO, INPUT);  
  delay(2000);
}

void loop() {  
  int gas = digitalRead(GAS_GPIO);  
  SerialBT.println(gas);
  delay(1000);
}