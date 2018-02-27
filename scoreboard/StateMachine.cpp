#include "StateMachine.h"



StateMachine::StateMachine()
{
}


StateMachine::~StateMachine()
{
}

void StateMachine::start()
{
	state = std::shared_ptr(new StartState());
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
ConnectState::ConnectState(Configuration *cfg): cfg(cfg)
{
	wsHandler = std::shared_ptr(new WebSocketHandler(cfg.m_config.hostIp, cfg.hostPort));
}

std::shared_ptr<State> UpdateConfigState::handle()
{
	
}


std::shared_ptr<State> ConnectState::handle()
{
	if (!connectToWifi(cfg->ssid, cfg->password)) {
		return std::shared_ptr(new SleepState(cfg));
	}
	if(!openWebSocket(cfg->hostIp, cfg->hostPort)){
		return std::shared_ptr(new SleepState(cfg));
	}
	if(!handshake(port)){
		return std::shared_ptr(new SleepState(cfg));
	}
	return std::shared_ptr(new ShowScoreState(cfg, wfClient, wsClient));
}



std::shared_ptr<State> SleepState::handle()
{
	ESP.deepSleep(0);
}
