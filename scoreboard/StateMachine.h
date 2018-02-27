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
	State(Configuration *cfg): cfg(cfg){}
	virtual ~State() {}
	virtual std::shared_ptr<State> handle() = 0;
private:
	Configuration* cfg;
};
class StartState : public State{
	virtual std::shared_ptr<State> handle();
	private Configuration *cfg;
};
class UpdateConfigState : public State {
	State(Configuration *cfg): cfg(cfg){}
	virtual std::shared_ptr<State> handle() {
		Serial.println("In UpdateConfigState");
	}
private:
	ConfigServer server;
};
class ConnectState : public State {
	virtual std::shared_ptr<State> handle() {
		Serial.println("In ConnectState");
	}
};
