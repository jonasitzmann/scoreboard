#include "ScoreboardController.h"
#include <memory>
#include "SerialLogger.h"
using namespace std;
shared_ptr<ScoreboardController> controller;
void setup() {
	shared_ptr<ILogger> logger = make_shared<SerialLogger>();
	controller = make_shared<ScoreboardController>(logger);
}

void loop() {
 controller->update();
}
