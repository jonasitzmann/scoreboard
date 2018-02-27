#include "StateMachine.h"



StateMachine::StateMachine()
{
}


StateMachine::~StateMachine()
{
}

void StateMachine::start()
{
	//define end set pins
	pinMode(buttonPin, INPUT);
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);    // turn the LED off
	Serial.println("");
	Serial.println("load configuration...");
	cfg.load();
	server.config = cfg;
	Serial.println("configuration loaded:");
	Serial.println(cfg.toString());
	Serial.println("create objects");
	wsHandler = *new WebSocketHandler(cfg.ssid, cfg.password, cfg.m_config.hostIp, cfg.hostPort);
	leds = *new LedDisplay(D1, 70, cfg.useEmulator);
	Serial.println("initialized!");
	Serial.println("\n\n");
	state = new StartState(this);
}

State * StartState::execute()
{
	bool updateConfig = digitalRead(stateMachine->buttonPin) == HIGH? true:false;
	if (updateConfig) {
		return new UpdateConfigState(stateMachine);
	}
	else {
		return new ConnectState();
	}
}
