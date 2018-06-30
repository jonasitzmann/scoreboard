#pragma once
#include "InputDevice.h"
#include "OutputDevice.h"
#include "ServerInOut.h"
#include "ScoreboardData.h"
#include <vector>
#include <memory>
#include "IConfigLoader.h"
#include "LoggerFactory.h"
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
	ILogger& logger;
public:
	ScoreboardController();
	void collectInputCommands();
	bool executeInputCommands();
	void update();
	void addInputDevice(shared_ptr<InputDevice> inputDevice);
	void addOutputDevice(shared_ptr<OutputDevice> outputDevice);
};
