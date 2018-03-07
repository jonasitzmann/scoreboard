#include "StateMachine.h"


std::shared_ptr<State> SleepState::handle()
{
	Serial.println("Going to sleep...");
	ESP.deepSleep(0);
}