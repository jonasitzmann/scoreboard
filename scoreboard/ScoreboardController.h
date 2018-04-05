#pragma once
#include "InputDevice.h"
#include "OutputDevice.h"
#include "ServerOutput.h"
#include <vector>
#include <memory>
using namespace std;
class ScoreboardController
{
	vector<shared_ptr<InputDevice>> inputDevices;
	vector<shared_ptr<OutputDevice>> outputDevices;
	int lScore, rScore;
	Color lColor, rColor;
public:
	ScoreboardController();
	~ScoreboardController();
	void update();
	void addInputDevice(shared_ptr<InputDevice> inputDevice);
	void addOutputDevice(shared_ptr<OutputDevice> outputDevice);

};

