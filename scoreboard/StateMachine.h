#pragma once
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
class StateMachine
{
public:
	StateMachine();
	~StateMachine();
	void start();
	State* state;
	LedDisplay leds;
	WebSocketHandler wsHandler;
	ScoreboardConfiguration cfg;
	ConfigServer server;
	int buttonPin = D6;
	int ledPin = D7;

};

class State{
public:
	virtual ~State() {}
	virtual State* handle() = 0;
};
class StartState : public State{
	State(Configuration *cfg);
	virtual State* execute();
	private Configuration *cfg;
};
class UpdateConfigState : public State {
	virtual State* execute() {
		Serial.println("In UpdateConfigState");
	}
};
class ConnectState : public State {
	virtual State* execute() {
		Serial.println("In ConnectState");
	}
};
