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
	virtual std::shared_ptr<State> handle();
	ConfigServer server;
public:
	UpdateConfigState(Configuration *cfg): cfg(cfg){}

};
class ConnectState : public State {
	virtual std::shared_ptr<State> handle();
	WebsocketHandler wsHandler;
public:
	ConnectState(Configuration *cfg): cfg(cfg){}

};
class ShowScoreState: public State{
	virtual std::shared_ptr<State> handle();
	std::shared_ptr<WebsocketHandler> wsHandler;
public:
	ConnectState(Configuration *cfg, std::shared_ptr<WebsocketHandler> wsHandler):
		cfg(cfg),
		wsHandler(wsHandler)
		{}
}
class SleepState: public State{
	virtual std::shared_ptr<State> handle();
public:
	SleepState(Configuration *cfg){}
