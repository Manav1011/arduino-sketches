#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
int MQ3 = A0;
int Relay = 6;
int value;
int R_led = 3;
int G_led = 4;
int buzzer = 5;
void setup() {
pinMode(MQ3, INPUT);
pinMode(Relay, OUTPUT);
digitalWrite(Relay, LOW);
pinMode(R_led, OUTPUT); // declare Red LED as output
pinMode(G_led, OUTPUT); // declare Green LED as output
pinMode(buzzer, OUTPUT); // declare Buzzer as output
}
void loop() {
value = analogRead(MQ3);
if (value > 900) {
digitalWrite(Relay, LOW);
digitalWrite(buzzer, HIGH);
digitalWrite(G_led, LOW); // Turn LED off.
digitalWrite(R_led, HIGH); // Turn LED on.
} else {
digitalWrite(Relay, HIGH);
digitalWrite(buzzer, LOW);
digitalWrite(G_led, HIGH); // Turn LED off.
digitalWrite(R_led, LOW); // Turn LED on.
}
Serial.begin(9600);
lcd.begin(16, 2);
lcd.setCursor(0, 0);
lcd.print(" Alcohol ");
lcd.setCursor(0, 1);
lcd.print(" Detection ");
delay(3000);
lcd.clear();
//Serial.println(value);
lcd.setCursor(0, 0);
lcd.print("Alcohol :");
lcd.setCursor(11, 0);
lcd.print(value);
delay(3000);
lcd.clear();
delay(500);
}