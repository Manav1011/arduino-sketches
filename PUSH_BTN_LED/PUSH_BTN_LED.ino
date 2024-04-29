#define BTN_PIN 2
#define LED_PIN 7
int ButtonState;
void setup() {  
  Serial.begin(9600);
  pinMode(7,OUTPUT);
  pinMode(2,INPUT);  

}

void loop() {  
    digitalWrite(LED_PIN,digitalRead(BTN_PIN));  
}
