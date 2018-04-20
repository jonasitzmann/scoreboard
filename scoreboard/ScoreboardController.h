#pragma once
#include "InputDevice.h"
#include "OutputDevice.h"
#include "ServerInOut.h"
#include "ScoreboardData.h"
#include <vector>
#include <memory>
#include "IConfigLoader.h"
using namespace std;
class ScoreboardController
{
	ScoreboardData data;
	vector<shared_ptr<InputDevice>> inputDevices;
	vector<shared_ptr<OutputDevice>> outputDevices;
	shared_ptr<IConfigLoader> configLoader;
public:
	ScoreboardController();
	vector<InputDevice::Input> collectInputCommands();
	bool executeInputCommands(vector<InputDevice::Input> inputs);
	void update();
	void addInputDevice(shared_ptr<InputDevice> inputDevice);
	void addOutputDevice(shared_ptr<OutputDevice> outputDevice);

};

