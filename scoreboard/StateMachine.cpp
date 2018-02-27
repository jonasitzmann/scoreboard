#include "StateMachine.h"



StateMachine::StateMachine()
{
}


StateMachine::~StateMachine()
{
}

void StateMachine::start()
{
	state = new StartState();
	while(true){
		state = state.handle();
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
	//wsHandler = *new WebSocketHandler(cfg.ssid, cfg.password, cfg.m_config.hostIp, cfg.hostPort);
	//leds = *new LedDisplay(D1, 70, cfg.useEmulator);
	if(digitalRead(buttonPin) = HIGH){
		return std::shared_ptr<UpdateConfigState>(new UpdateConfigState(cfg));
	}
	else{
		return std::shared_ptr<ConnectState>(new ConnectState(cfg));
	}
}
std::shared_ptr<State> UpdateConfigState::handle()
{

}
