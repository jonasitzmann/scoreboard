#include "ScoreboardController.h"
ScoreboardController* controller = nullptr;
void setup() {
	Serial.begin(115200);
	delay(100);
	Serial.println();
  controller = new ScoreboardController();
}

void loop() {
  controller->update();
}
