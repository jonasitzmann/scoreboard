#include "StateMachine.h"
#include <memory>
void StateMachine::start()
{
	state = std::make_shared<ShowScoreOfflineState>();
	while(true){
		Serial.println("New State: " + state->getName());
		state = state->handle();
	}
}
