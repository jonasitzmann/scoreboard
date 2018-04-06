#include "ScoreboardController.h"
#include <set>
ScoreboardController::ScoreboardController()
{
	data.trust = 0; // overwrite the initial data by trusted information sources only
	addInputDevice(make_shared<SerialInput>());
	addInputDevice(make_shared<ButtonInput>());
	addOutputDevice(make_shared<LedOutput>());
	LedDisplay ledDisplay(D5, 72, true);
	ledDisplay.setPixel(35, Color());
	ledDisplay.setPixel(36, Color());
	auto ledOutput = std::make_shared<LedOutput>();
	ledOutput->leds = ledDisplay;
	addOutputDevice(ledOutput);
	auto serverInOut = make_shared<ServerOutput>();
	addInputDevice(serverInOut);
	addOutputDevice(serverInOut);
	executeInputCommands({ InputDevice::RESET });
}


ScoreboardController::~ScoreboardController()
{
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
	bool ok = true;
	// process each input using all output devices
	for (auto itr = inputs.begin(); itr != inputs.end(); ++itr)
	{
		switch (*itr)
		{
		case InputDevice::L_PLUS:
		{
			data.score1 = min(data.score1 + 1, 99);
			for (auto outputItr = outputDevices.begin(); outputItr != outputDevices.end(); ++outputItr)
			{
				ok &= (*outputItr)->updateLScore(data.score1);
			}
		}
		break;
		case InputDevice::L_MINUS:
		{
			data.score1 = max(data.score1 - 1, 0);
			for (auto outputItr = outputDevices.begin(); outputItr != outputDevices.end(); ++outputItr)
			{
				ok &= (*outputItr)->updateLScore(data.score1);
			}
		}
		break;
		case InputDevice::R_PLUS:
		{
			data.score2 = min(data.score2 + 1, 99);
			for (auto outputItr = outputDevices.begin(); outputItr != outputDevices.end(); ++outputItr)
			{
				ok &= (*outputItr)->updateRScore(data.score2);
			}
		}
		break;
		case InputDevice::R_MINUS:
		{
			data.score2 = max(data.score2 - 1, 0);
			for (auto outputItr = outputDevices.begin(); outputItr != outputDevices.end(); ++outputItr)
			{
				ok &= (*outputItr)->updateRScore(data.score2);
			}
		}
		break;
		case InputDevice::L_COLOR:
		{
			data.color1.changeToNext();
			for (auto outputItr = outputDevices.begin(); outputItr != outputDevices.end(); ++outputItr)
			{
				ok &= (*outputItr)->updateLColor(data.color1);
			}
		}
		break;
		case InputDevice::R_COLOR:
		{
			data.color2.changeToNext();
			for (auto outputItr = outputDevices.begin(); outputItr != outputDevices.end(); ++outputItr)
			{
				ok &= (*outputItr)->updateRColor(data.color2);
			}
		}
		break;
		case InputDevice::RESET:
		{
			for (auto inputItr = inputDevices.begin(); inputItr != inputDevices.end(); ++inputItr)
			{
				ScoreboardData dataCandidate = (*inputItr)->init();
				if (dataCandidate.trust > data.trust)
				{
					data = dataCandidate;
				}
			}
			data.trust = 0;
			for (auto outputItr = outputDevices.begin(); outputItr != outputDevices.end(); ++outputItr)
			{
				(*outputItr)->updateAll(data.score2, data.score1, data.color2, data.color1);
			}
		}
		default:
			break;
		}
	}
	return ok;
}

void ScoreboardController::update()
{
	auto inputs = collectInputCommands();
	bool ok = executeInputCommands(inputs);
	if (!ok)
	{
		Serial.println("could not execute input command");
		Serial.println("performing reset");
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
