#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "Manav Shah 4G";
const char* password = "9925717005ms";
int WIFI_PIN = 5;
int TV_PIN = 4;
int SETTOP_BOX_PIN = 2;
int THIRD_SWITCH_PIN = 18;

int WIFI_STATE;
int TV_STATE;
int THIRD_SWITCH_STATE;

// Create an instance of the web server on port 80
WebServer server(80);

String SendHTML(int TV_STATE, int THIRD_SWITCH_STATE) {
  String dynamic_html = "";
  dynamic_html += "<!DOCTYPE html><html lang=\"en\"><head>";
  dynamic_html += "<meta charset=\"UTF-8\">";
  dynamic_html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  dynamic_html += "<title>ESP32 Control Panel</title>";
  dynamic_html += "<style>\n";
  dynamic_html += "html, body, #main-container {height: 100%; width: 100%;}\n";
  dynamic_html += "body {background: rgb(244, 246, 248); background: linear-gradient(35deg, rgb(16, 15, 16) 0%, rgb(32, 31, 32) 100%); margin: 0;}\n";
  dynamic_html += ".button-49,.button-49:after{text-decoration:none;text-align:center;font-size:20px;font-family:'Bebas Neue',sans-serif;border:0;color:#fff;cursor:pointer;letter-spacing:3px;box-shadow:6px 0 0 #fff;outline:transparent;position:relative;user-select:none;-webkit-user-select:none;touch-action:manipulation}\n";
  dynamic_html += ".button-49, .button-49:after {min-width: 300px; line-height: 88px;}\n";
  dynamic_html += "</style>\n";
  dynamic_html += "</head><body>";
  dynamic_html += "<div style=\"display:flex;flex-direction: column; justify-content: center; align-items: center; gap: 20px;\" id=\"main-container\">";
  dynamic_html += "<button class=\"button-49\" style=\"background:green\" role=\"button\">WIFI : ON</button>";
  if (TV_STATE == LOW) {
    dynamic_html += "<a href=\"/tv_off\" class=\"button-49\" style=\"background:green\" role=\"button\">TV : ON</a>";
  } else {
    dynamic_html += "<a href=\"/tv_on\" class=\"button-49\" style=\"background:red\" role=\"button\">TV : OFF</a>";
  }
  if (THIRD_SWITCH_STATE == LOW) {
    dynamic_html += "<a href=\"/third_switch_off\" class=\"button-49\" style=\"background:green\" role=\"button\">3rd Switch : ON</a>";
  } else {
    dynamic_html += "<a href=\"/third_switch_on\" class=\"button-49\" style=\"background:red\" role=\"button\">3rd Switch : OFF</a>";
  }
  dynamic_html += "</div>";
  dynamic_html += "</body></html>";
  return dynamic_html;
}

void base_state() {
    server.send(200, "text/html", SendHTML(TV_STATE, THIRD_SWITCH_STATE)); 
}

void tv_on() {
    digitalWrite(TV_PIN, LOW);
    digitalWrite(SETTOP_BOX_PIN, LOW);
    TV_STATE = digitalRead(TV_PIN);
    server.send(200, "text/html", SendHTML(TV_STATE, THIRD_SWITCH_STATE)); 
}

void tv_off() {
    digitalWrite(TV_PIN, HIGH);
    digitalWrite(SETTOP_BOX_PIN, HIGH);
    TV_STATE = digitalRead(TV_PIN);
    server.send(200, "text/html", SendHTML(TV_STATE, THIRD_SWITCH_STATE)); 
}

void third_switch_on() {
    digitalWrite(THIRD_SWITCH_PIN, LOW);    
    THIRD_SWITCH_STATE = digitalRead(THIRD_SWITCH_PIN);
    server.send(200, "text/html", SendHTML(TV_STATE, THIRD_SWITCH_STATE)); 
}

void third_switch_off() {
    digitalWrite(THIRD_SWITCH_PIN, HIGH);    
    THIRD_SWITCH_STATE = digitalRead(THIRD_SWITCH_PIN);
    server.send(200, "text/html", SendHTML(TV_STATE, THIRD_SWITCH_STATE)); 
}

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);
  pinMode(WIFI_PIN, OUTPUT);
  pinMode(TV_PIN, OUTPUT);
  pinMode(SETTOP_BOX_PIN, OUTPUT);
  pinMode(THIRD_SWITCH_PIN, OUTPUT);

  digitalWrite(WIFI_PIN,LOW);

  WIFI_STATE = digitalRead(WIFI_PIN);
  TV_STATE = digitalRead(TV_PIN);     
  THIRD_SWITCH_STATE = digitalRead(THIRD_SWITCH_PIN);    


  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Define the root URL handling function
  server.on("/", base_state);
  server.on("/tv_on", tv_on);
  server.on("/tv_off", tv_off);
  server.on("/third_switch_on", third_switch_on);
  server.on("/third_switch_off", third_switch_off);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle client requests
  server.handleClient();
}