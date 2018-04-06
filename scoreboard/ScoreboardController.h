#pragma once
#include "InputDevice.h"
#include "OutputDevice.h"
#include "ServerInOut.h"
#include "ScoreboardData.h"
#include <vector>
#include <memory>
using namespace std;
class ScoreboardController
{
	ScoreboardData data;
	vector<shared_ptr<InputDevice>> inputDevices;
	vector<shared_ptr<OutputDevice>> outputDevices;
public:
	ScoreboardController();
	~ScoreboardController();
	vector<InputDevice::Input> collectInputCommands();
	bool executeInputCommands(vector<InputDevice::Input> inputs);
	void update();
	void addInputDevice(shared_ptr<InputDevice> inputDevice);
	void addOutputDevice(shared_ptr<OutputDevice> outputDevice);

};

