#include "StateMachine.h"
void setup() {
	Serial.begin(115200);
	Serial.println("Started");
	int pins[] = { D1, D2, D3, D4 };
	for (int i = 0; i < (sizeof(pins) / sizeof(pins[0])); ++i) {
		int pin = pins[i];
		pinMode(pin, INPUT_PULLUP);
	}
	StateMachine stateMachine = *new StateMachine();
	stateMachine.start();
}


void loop() {

}
