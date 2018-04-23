#include "ScoreboardController.h"
#include <set>
ScoreboardController::ScoreboardController()
{
	addInputDevice(make_shared<SerialInput>());
	addInputDevice(make_shared<ButtonInput>());
	addOutputDevice(make_shared<LedOutput>());
	auto serverInOut = make_shared<ServerInOut>();
	addOutputDevice(serverInOut);
	configLoader = serverInOut;
	data = configLoader->loadConfig();
}

void ScoreboardController::collectInputCommands()
{
		for_each(begin(inputDevices), end(inputDevices), [&](shared_ptr<InputDevice> device) {
		auto newInputs = device->getInput();
		inputCommands.insert(end(inputCommands), begin(newInputs), end(newInputs));
	});
}

bool ScoreboardController::executeInputCommands()
{

	if (inputCommands.empty()) return true;
	bool ok = true;
	for (auto itr = inputCommands.begin(); itr != inputCommands.end(); ++itr)
	{
		switch (*itr)
		{
		case InputDevice::L_PLUS:
		{
			if (data.locked) break;
			data.score1 = min(data.score1 + 1, 99);
			break;
		}
		case InputDevice::L_MINUS:
		{
			if (data.locked) break;
			data.score1 = max(data.score1 - 1, 0);
		}
		break;
		case InputDevice::R_PLUS:
		{
			if (data.locked) break;
			data.score2 = min(data.score2 + 1, 99);
		}
		break;
		case InputDevice::R_MINUS:
		{
			if (data.locked) break;
			data.score2 = max(data.score2 - 1, 0);
		}
		break;
		case InputDevice::L_COLOR:
		{
			if (data.locked) break;
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
			if (data.locked) break;
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
			if (data.locked) break;
			data.swappedSides = !data.swappedSides;
			break;
		}
		case InputDevice::LOCK:
		{
			data.locked = true;
			break;
		}
		case InputDevice::UNLOCK:
		{
			data.locked = false;
			break;
		}
		case InputDevice::RESET:
		{
			reset();
			break;
		}
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
	collectInputCommands();
	if (!executeInputCommands())
	{
		Serial.println("could not execute input command\nperforming reset");
		reset();
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

void ScoreboardController::reset()
{
	data = configLoader->loadConfig();
}
