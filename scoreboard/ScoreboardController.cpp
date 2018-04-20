#include "ScoreboardController.h"
#include <set>
ScoreboardController::ScoreboardController()
{
	addInputDevice(make_shared<SerialInput>());
	addInputDevice(make_shared<ButtonInput>());
	addOutputDevice(make_shared<LedOutput>());
	auto serverInOut = make_shared<ServerInOut>();
	addInputDevice(serverInOut);
	addOutputDevice(serverInOut);
	configLoader = serverInOut;
	data = configLoader->loadConfig();
}

std::vector<InputDevice::Input> ScoreboardController::collectInputCommands()
{
	// collect inputs from all devices
	vector<InputDevice::Input> inputs;
	for (auto itr = inputDevices.begin(); itr != inputDevices.end(); ++itr)
	{
		auto input = (*itr)->getInput();
		if (input != InputDevice::NO_INPUT)
		{
			inputs.push_back(input);
		}
	}
	return inputs;
}

bool ScoreboardController::executeInputCommands(vector<InputDevice::Input> inputs)
{
	if (inputs.empty()) return true;
	bool ok = true;
	// process each input using all output devices
	for (auto itr = inputs.begin(); itr != inputs.end(); ++itr)
	{
		switch (*itr)
		{
		case InputDevice::L_PLUS:
		{
			if (data.scoreIsFinal) break;
			data.score1 = min(data.score1 + 1, 99);
			break;
		}
		case InputDevice::L_MINUS:
		{
			if (data.scoreIsFinal) break;
			data.score1 = max(data.score1 - 1, 0);
		}
		break;
		case InputDevice::R_PLUS:
		{
			if (data.scoreIsFinal) break;
			data.score2 = min(data.score2 + 1, 99);
		}
		break;
		case InputDevice::R_MINUS:
		{
			if (data.scoreIsFinal) break;
			data.score2 = max(data.score2 - 1, 0);
		}
		break;
		case InputDevice::L_COLOR:
		{
			if (data.scoreIsFinal) break;
			int &colorIndex = data.colorIndex1;
			vector<shared_ptr<Color>> &colorList = data.colorList1;
			if (colorList.empty())
			{
				Serial.println("no colors available!");
				break;
			}
			if (data.swappedSides)
			{
				colorIndex = data.colorIndex2;
				colorList = data.colorList2;
			}
			++colorIndex;
			colorIndex %= colorList.size();
		}
		break;
		case InputDevice::R_COLOR:
		{
			if (data.scoreIsFinal) break;
			int &colorIndex = data.colorIndex2;
			vector<shared_ptr<Color>> &colorList = data.colorList2;
			if (colorList.empty())
			{
				Serial.println("no colors available!");
				break;
			}
			if (data.swappedSides)
			{
				colorIndex = data.colorIndex1;
				colorList = data.colorList1;
			}
			++colorIndex;
			colorIndex %= colorList.size();
		}
		break;
		case InputDevice::SWAP:
		{
			if (data.scoreIsFinal) break;
			data.swappedSides = !data.swappedSides;
			break;
		}
		case InputDevice::END:
		{
			data.scoreIsFinal = true;
			break;
		}
		case InputDevice::RESUME:
		{
			data.scoreIsFinal = false;
			break;
		}
		case InputDevice::RESET:
		{
			data = configLoader->loadConfig();
		}
		break;
		default:
			break;
		}
	}
	for (auto outputItr = outputDevices.begin(); outputItr != outputDevices.end(); ++outputItr)
	{
		ok &= (*outputItr)->update(data);
	}
	return ok;
}

void ScoreboardController::update()
{
	auto inputs = collectInputCommands();
	bool ok = executeInputCommands(inputs);
	if (!ok)
	{
		Serial.println("could not execute input command\nperforming reset");
		executeInputCommands({ InputDevice::RESET });
	}
}

void ScoreboardController::addInputDevice(shared_ptr<InputDevice> inputDevice)
{
	inputDevices.push_back(inputDevice);
}

void ScoreboardController::addOutputDevice(shared_ptr<OutputDevice> outputDevice)
{
	outputDevices.push_back(outputDevice);
}
