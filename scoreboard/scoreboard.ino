#include <ESP8266WiFi.h>
#include <WebSocketClient.h>
#include "LedDisplay.h"
#include "WebSocketHandler.h"
#include <WString.h>
#include "configurations.h"
LedDisplay leds = *new LedDisplay(D1, 70, true);
WebSocketHandler wsHandler = * new WebSocketHandler();
void setup() {
  Serial.begin(115200);
  Configuration cfg;
  char hostIp[] = "123.456.789";
  strncpy(cfg.hostIp, hostIp, sizeof(hostIp)); 
  cfg.save();
  auto cfgLoaded = Configuration::load();
  Serial.print("Host: ");
  Serial.println(cfgLoaded.hostIp);
  wsHandler.connectToServer();
}


void loop() {
  if (wsHandler.isConnected()) {
  
    String data = wsHandler.getData();
    if (data.length() > 0 && String(data.toInt()) == data) {
      leds.showDigit(data.toInt());

    }
  }
  else {
    Serial.println("Connection lost! Trying to reconnect...");
    wsHandler.connectToServer();
  }
}
