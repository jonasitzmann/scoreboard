#include "ScoreboardController.h"
#include <memory>
using namespace std;
shared_ptr<ScoreboardController> controller;
void setup() {
	Serial.begin(115200);
	delay(100);
	Serial.println();
	controller = make_shared<ScoreboardController>();
}

void loop() {
  controller->update();
}
