#pragma once
#include "InputDevice.h"
#include "OutputDevice.h"
#include "ServerInOut.h"
#include "ScoreboardData.h"
#include <vector>
#include <memory>
#include "IConfigLoader.h"
#include "SerialLogger.h"
#include "WiFiWrapper.h"
#include "HttpWrapper.h"
using namespace std;
class ScoreboardController
{
	ScoreboardData data;
	vector<shared_ptr<InputDevice>> inputDevices;
	vector<shared_ptr<OutputDevice>> outputDevices;
	shared_ptr<IConfigLoader> configLoader;
	vector<InputDevice::Input> inputCommands;
	shared_ptr<ILogger> logger;
public:
	ScoreboardController(shared_ptr<ILogger> logger);
	void collectInputCommands();
	bool executeInputCommands();
	void update();
	void addInputDevice(shared_ptr<InputDevice> inputDevice);
	void addOutputDevice(shared_ptr<OutputDevice> outputDevice);
};

