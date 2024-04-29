#define ANALOG_PIN A0
#define DIGITAL_PIN 2
void setup() {
  Serial.begin(9600);  
  pinMode(DIGITAL_PIN, INPUT);
}

void loop() {
  int analogValue = analogRead(ANALOG_PIN);
  
  // Read digital value
  int digitalValue = digitalRead(DIGITAL_PIN);
  // Print values to serial monitor
  Serial.print("Analog Value: ");
  Serial.print(analogValue);
  Serial.print("\tDigital Value: ");
  Serial.println(digitalValue);
  delay(1000); // Delay for 1 second
}
