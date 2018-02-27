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
	bool editConfig = false;
	int buttonPin = D6;
	int ledPin = D7;

};

class State{
public:
	State(StateMachine* const stateMachine) :stateMachine(stateMachine) {}
	virtual ~State() {}
	virtual State* execute() = 0;
protected:
	StateMachine * const stateMachine;
};
class StartState : public State{
	virtual State* execute();
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