#include "ScoreboardController.h"
#include <memory>
#include "SerialLogger.h"
using namespace std;
shared_ptr<ScoreboardController> controller;
void setup() {
	controller = make_shared<ScoreboardController>();
}

void loop() {
 controller->update();
}
