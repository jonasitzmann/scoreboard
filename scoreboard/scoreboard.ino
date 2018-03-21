#include "StateMachine.h"
void setup() {
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(D1, INPUT);
	pinMode(D2, INPUT);
	pinMode(D3, INPUT);
	pinMode(D7, OUTPUT);

	digitalWrite(LED_BUILTIN, HIGH);
	Serial.println("Started");
	StateMachine stateMachine = *new StateMachine();
	stateMachine.start();
}


void loop() {
	Serial.printf("D1: %d\t", digitalRead(D1));
	Serial.printf("D2: %d\t", digitalRead(D2));
	Serial.printf("D3: %d\t", digitalRead(D3));
	Serial.printf("D4: %d\n", digitalRead(D4));
	Serial.printf("D5: %d\t", digitalRead(D5));
	Serial.printf("D6: %d\t", digitalRead(D6));
	Serial.printf("D7: %d\t", digitalRead(D7));
	Serial.printf("D8: %d\n\n", digitalRead(D8));
	delay(2000);
}
