#include "StateMachine.h"

void setup() {
	Serial.begin(115200);
}


void loop() {
	digitalWrite(ledPin, editConfig?HIGH:LOW);
	if (!editConfig && digitalRead(buttonPin) == HIGH) {
		Serial.println("updating Config");
		editConfig = true;
		server.start();
	}
	if (editConfig) {
		bool configChanged;
		cfg = server.updateConfig(configChanged);
		if (configChanged) {
			editConfig = false;
			Serial.println("Config updated");
		}
	}
	else {
		if (wsHandler.isConnected()) {

			String data = wsHandler.getData();
			if (data.length() > 0 && String(data.toInt()) == data) {
				leds.showNumber(data.toInt());
			}
		}
		else {
			Serial.println("Connection lost! Trying to reconnect...");
			wsHandler.connectToServer();
		}
	}
}
