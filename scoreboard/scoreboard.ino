#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <WebSocketClient.h>
#include "LedDisplay.h"
#include "WebSocketHandler.h"
#include <WString.h>
#include "configurations.h"
#include <WiFiClient.h>
#include "ConfigServer.h"
#include <ESP8266WebServer.h>
LedDisplay leds;
WebSocketHandler wsHandler;
ScoreboardConfiguration cfg = *new ScoreboardConfiguration();
ConfigServer server;
bool editConfig = false;
int buttonPin = D6;
int ledPin = D7;

void setup() {
	Serial.begin(115200);
	pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
	Serial.println("");
	cfg.load();
	delay(100);
	wsHandler = *new WebSocketHandler(cfg.ssid, cfg.password, cfg.m_config.hostIp, cfg.hostPort);
	leds = *new LedDisplay(D1, 70, cfg.useEmulator);
  server.config = cfg;
	loop();
}


void loop() {
	digitalWrite(ledPin, editConfig?HIGH:LOW);
	if (!editConfig && digitalRead(buttonPin) == HIGH) {
		Serial.println("updating Config");
		editConfig = true;
		server.start();
	}
	if (editConfig) {
		bool configChanged;
		cfg = server.updateConfig(configChanged);
		if (configChanged) {
			editConfig = false;
			Serial.println("Config updated");
		}
	}
	else {
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
}
