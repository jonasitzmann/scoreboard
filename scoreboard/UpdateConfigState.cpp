#include "StateMachine.h"


std::shared_ptr<State> UpdateConfigState::handle()
{
	digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
	server.start();

	while (!server.configChanged) {
		server.updateConfig(); //TODO Add timeout?
	}
	Serial.println("configuration updateted: ");
	Serial.println(cfg->toString());
	delay(1000); //wait for the feedback page to load
	server.terminate();
	digitalWrite(LED_BUILTIN, HIGH);
	return std::make_shared<ShowScoreOfflineState>(cfg);
}