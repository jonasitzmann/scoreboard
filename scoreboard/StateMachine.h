#pragma once
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <WebSocketClient.h>
#include "LedDisplay.h"
#include "WebSocketHandler.h"
#include <WString.h>
#include "configuration.h"
#include <WiFiClient.h>
#include "ConfigServer.h"
#include <ESP8266WebServer.h>
#include <memory>
#include "Color.h"
#include "InputDevice.h"


class State{
public:
	State(std::shared_ptr<Configuration>cfg): cfg(cfg){}
	State() : cfg(nullptr){}
	virtual ~State() {}
	virtual std::shared_ptr<State> handle() = 0;
	virtual String getName() { return "State";}
protected:
	std::shared_ptr<Configuration> cfg;
private:
};

class StartState : public State {
	int buttonPin = D1;
	int ledPin = BUILTIN_LED;
public:
	StartState() : State(std::shared_ptr<Configuration>()) {
		pinMode(buttonPin, INPUT);
		pinMode(ledPin, OUTPUT);
		cfg = std::make_shared<Configuration>();
	}
	virtual std::shared_ptr<State> handle();
	virtual String getName() { return "StartState"; }
};

class UpdateConfigState : public State {
	ConfigServer server;
	UpdateConfigState();
public:
	UpdateConfigState(std::shared_ptr<Configuration>cfg): State(cfg), server(cfg){}
	virtual std::shared_ptr<State> handle();
	virtual String getName() { return "UpdateConfigState"; }
};

class ConnectState : public State {
	std::shared_ptr<WiFiClient> wfClient;
	std::shared_ptr<WebSocketClient> wsClient;
	bool connectToWiFi();
	bool openWebSocket();
	bool handshake();
public:
	virtual std::shared_ptr<State> handle();
	ConnectState(std::shared_ptr<Configuration>cfg) :
		State(cfg) {
		wfClient = std::make_shared<WiFiClient>();
		wsClient = std::make_shared<WebSocketClient>();
	}
	virtual String getName() { return "ConnectState"; }
};



class ShowScoreOfflineState : public State {
	InputDevice* inputDevice;
	LedDisplay display;
	int lScore;
	Color lColor;
	int rScore;
	Color rColor;
	Color::ColorType rColorType, lColorType;
	int upPin, downPin, colorPin;
	bool upButtonPressedBefore, downButtonPressedBefore, colorButtonPressedBefore;
	void setLScore(int newScore);
	void setRScore(int newScore);
	void setLColor(Color::ColorType newColor);
	void setRColor(Color::ColorType newColor);
	Color::ColorType getNextColor(Color::ColorType type);
public:
	ShowScoreOfflineState();
	ShowScoreOfflineState(std::shared_ptr<Configuration> cfg);
	virtual std::shared_ptr<State> handle();
	virtual String getName();


};


class ShowScoreState: public State{
	std::shared_ptr<WiFiClient> wfClient;
	std::shared_ptr<WebSocketClient> wsClient;
	LedDisplay display;
	int score;
	Color color;
	void setScore(int newScore);
	void setColor(Color newColor);
public:
	ShowScoreState(std::shared_ptr<Configuration>cfg, std::shared_ptr<WiFiClient> wfClient, std::shared_ptr<WebSocketClient> wsClient) :
		State(cfg), wfClient(wfClient), wsClient(wsClient), score(0), color()
	{
		display = LedDisplay(D6, cfg->numPixels, false);
	}
	virtual std::shared_ptr<State> handle();
	virtual String getName() { return "ShowScoreState"; }
};

class SleepState : public State {
public:
	SleepState(std::shared_ptr<Configuration>cfg): State(cfg){}
	virtual std::shared_ptr<State> handle();
	virtual String getName() { return "SleepState"; }
};

class StateMachine
{
	std::shared_ptr<State> state;
public:
	void start();
	std::shared_ptr<Configuration> cfg;
};