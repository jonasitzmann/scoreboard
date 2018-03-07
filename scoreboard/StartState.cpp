#include "StateMachine.h"

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
	if (digitalRead(buttonPin) == HIGH) {
		return std::make_shared<UpdateConfigState>(cfg);
	}
	else {
		return std::make_shared<ConnectState>(cfg);
	}
}