#include "ScoreboardController.h"

ScoreboardController::ScoreboardController():
	lScore(0), rScore(0), lColor(), rColor()
{
	addInputDevice(make_shared<SerialInput>());
	addInputDevice(make_shared<ButtonInput>());
	addOutputDevice(make_shared<LedOutput>());
	LedDisplay ledDisplay(D5, 72, true);
	ledDisplay.setPixel(35, Color());
	ledDisplay.setPixel(36, Color());
	auto ledOutput = std::make_shared<LedOutput>();
	ledOutput->leds = ledDisplay;
	addOutputDevice(ledOutput);
	addOutputDevice(make_shared<ServerOutput>());
}


ScoreboardController::~ScoreboardController()
{
}

void ScoreboardController::update()
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

	// process each input using all output devices
	for (auto itr = inputs.begin(); itr != inputs.end(); ++itr)
	{
		switch (*itr)
		{
		case InputDevice::L_PLUS:
		{
			lScore = min(lScore + 1, 99);
			for (auto outputItr = outputDevices.begin(); outputItr != outputDevices.end(); ++outputItr)
			{
				(*outputItr)->updateLScore(lScore);
			}
		}
			break;
		case InputDevice::L_MINUS:
		{
			lScore = max(lScore - 1, 0);
			for (auto outputItr = outputDevices.begin(); outputItr != outputDevices.end(); ++outputItr)
			{
				(*outputItr)->updateLScore(lScore);
			}
		}
		break;		
		case InputDevice::R_PLUS:
		{
			rScore = min(rScore + 1, 99);
			for (auto outputItr = outputDevices.begin(); outputItr != outputDevices.end(); ++outputItr)
			{
				(*outputItr)->updateRScore(rScore);
			}
		}
		break;		
		case InputDevice::R_MINUS:
		{
			rScore = max(rScore - 1, 0);
			for (auto outputItr = outputDevices.begin(); outputItr != outputDevices.end(); ++outputItr)
			{
				(*outputItr)->updateRScore(rScore);
			}
		}
		break;		
		case InputDevice::L_COLOR:
		{
			lColor.changeToNext();
			for (auto outputItr = outputDevices.begin(); outputItr != outputDevices.end(); ++outputItr)
			{
				(*outputItr)->updateLColor(lColor);
			}
		}
		break;
		case InputDevice::R_COLOR:
		{
			rColor.changeToNext();
			for (auto outputItr = outputDevices.begin(); outputItr != outputDevices.end(); ++outputItr)
			{
				(*outputItr)->updateRColor(rColor);
			}
		}
		break;
		case InputDevice::RESET:
		{
			for (auto outputItr = outputDevices.begin(); outputItr != outputDevices.end(); ++outputItr)
			{
				rScore = 0;
				lScore = 0;
				rColor = Color();
				lColor = Color();
				(*outputItr)->updateAll(rScore, lScore, rColor, lColor);
			}
		}
		default:
			break;
		}
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
