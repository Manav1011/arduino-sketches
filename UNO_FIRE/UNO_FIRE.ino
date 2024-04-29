void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT);
}

void loop() {  
  if(digitalRead(2) == 0){
    Serial.println("AAG LAGADI....AAG LAGADI.....");
  }else{
    Serial.println("..............................");
  }
  delay(1000);
}
