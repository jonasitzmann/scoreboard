#include "StateMachine.h"
void setup() {
	Serial.begin(115200);
	Serial.println("Started");
	StateMachine stateMachine = *new StateMachine();
	stateMachine.start();
}


void loop() {
	Serial.println("in loop function");
}
