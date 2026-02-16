#include <WiFi.h>
#include <WebServer.h>
#include "secrets.h"

WebServer server(80);

HardwareSerial stm_esp(2); // UART2

uint16_t brightness = 0;

void sendBrightness() {
  String json = "{\"LED_Brightness\": " + String(brightness) + "}";
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", json);  
}

void setup() {
  Serial.begin(9600);    
  stm_esp.begin(115200, SERIAL_8N1, 16); 

  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED);
  Serial.println("\nIP: " + WiFi.localIP().toString());

  server.on("/brightness", sendBrightness);
  server.begin();
}

void loop() {
  server.handleClient();  
  brightness = stm_esp.read();
  Serial.print("Brightness: ");
  Serial.println(brightness); 
}

