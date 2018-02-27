#include "StateMachine.h"
#include <memory>
void StateMachine::start()
{
	state = std::make_shared<StartState>();
	while(true){
		Serial.println("New State: " + state->getName());
		state = state->handle();
	}
}

std::shared_ptr<State> StartState::handle()
{
	//define end set pins
	pinMode(buttonPin, INPUT);
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);    // turn the LED off
	Serial.println("");
	Serial.println("load configuration...");
	cfg->load();
	Serial.println("configuration loaded:");
	Serial.println(cfg->toString());
	if(digitalRead(buttonPin) == HIGH){
		return std::make_shared<UpdateConfigState>(cfg);
	}
	else{
		return std::make_shared<ConnectState>(cfg);
	}
}


std::shared_ptr<State> UpdateConfigState::handle()
{
	server.start();
	while (!server.configChanged) {
		server.updateConfig(); //TODO Add timeout?
	}
	delay(3000); //wait for the feedback page to load
	server.terminate();
	return std::make_shared<ConnectState>(cfg);
}


bool ConnectState::connectToWiFi()
{
	Serial.println("Connect to WiFi");
	int t0 = millis();
	WiFi.begin(cfg->ssid.c_str(), cfg->password.c_str());
	while (WiFi.status() != WL_CONNECTED) {
		if (millis() - t0 > 10000) {
			Serial.println();
			return false;
		}
		Serial.print(".");
		delay(300);
	}
	Serial.println();
	return true;
}

bool ConnectState::openWebSocket()
{
	Serial.println("Connect to Server");
	if (wfClient.get()->connect(cfg->hostIp, cfg->hostPort)) {
		Serial.println("Connection established.");
		return true;
	}
	else {
		Serial.println("Connection failed.");
		return false;
	}
}

bool ConnectState::handshake()
{
	wsClient.get()->path = "/";
	wsClient.get()->host = cfg->hostIp.c_str();
	if (wsClient.get()->handshake(*wfClient.get())){
		Serial.println("Handshake successful");
		return true;
	}
	else {
		Serial.println("Handshake failed.");
		return false;
	}
}

std::shared_ptr<State> ConnectState::handle()
{
	if (!connectToWiFi()) {
		return std::make_shared<SleepState>(cfg);
	}
	if(!openWebSocket()){
		return std::make_shared<SleepState>(cfg);
	}
	if(!handshake()){
		return std::make_shared<SleepState>(cfg);
	}
	return std::make_shared<ShowScoreState>(cfg, wfClient, wsClient);
}



std::shared_ptr<State> SleepState::handle()
{
	Serial.println("Going to sleep...");
	ESP.deepSleep(0);
}

std::shared_ptr<State> ShowScoreState::handle()
{
	while (wfClient->connected()) {
		String data;
		wsClient->getData(data);
		if (data.length() > 0 && String(data.toInt()) == data) {
			display.showNumber(data.toInt());
		}
	}
	return std::make_shared<StartState>();
}
