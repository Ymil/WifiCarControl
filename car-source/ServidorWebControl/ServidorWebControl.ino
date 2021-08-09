#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "./wifidef.h"


const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

void setup(void) {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", [](){
    server.send(200, "text/plain", "Controlador autito");
  });
  

  server.on("/up", []() {
    server.send(200, "text/plain", "");
    Serial.write("w\n");
  });

  server.on("/down", []() {
    server.send(200, "text/plain", "");
    Serial.write("s\n");
  });
  
  server.on("/left", []() {
    server.send(200, "text/plain", "");
    Serial.write("d\n");
  });

  server.on("/right", []() {
    server.send(200, "text/plain", "");
    Serial.write("a\n");
  });

  server.on("/break", []() {
    server.send(200, "text/plain", "");
    Serial.write("f\n");
  });
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
