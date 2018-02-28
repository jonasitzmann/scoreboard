#include "StateMachine.h"
void setup() {
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
	Serial.println("Started");
	StateMachine stateMachine = *new StateMachine();
	stateMachine.start();
}


void loop() {
	Serial.println("in loop function");
}
