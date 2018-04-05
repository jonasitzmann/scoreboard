#pragma once
#include "StateMachine.h"


String ShowScoreOfflineState::getName() {
	return "ShowScoreOfflineState";
}


ShowScoreOfflineState::ShowScoreOfflineState() :
	lColor(),
	rColor(),
	lScore(0),
	rScore(0),
	rColorType(Color::RED),
	lColorType(Color::BLUE),
	display(D6, 142, false) // USE_EMULATOR HARD CODED
{
	inputDevice = new ButtonInput();
}


ShowScoreOfflineState::ShowScoreOfflineState(std::shared_ptr<Configuration> cfg) :
	lColor(),
	rColor(),
	lScore(0),
	rScore(0),
	display(D6, cfg->numPixels, cfg->useEmulator)
{
	if (cfg->useEmulator) {
		inputDevice = new SerialInput();
	}
	else {
		inputDevice = new ButtonInput();
	}
}

std::shared_ptr<State> ShowScoreOfflineState::handle() {
	while (true) {
		auto input = inputDevice->getInput();
		switch (input) {
		case InputDevice::NO_INPUT:
			break;
		case InputDevice::L_PLUS:
			Serial.println("L_PLUS");
			setLScore(lScore + 1);
			break;
		case InputDevice::L_MINUS:
			Serial.println("L_MINUS");
			setLScore(lScore - 1);
			break;
		case InputDevice::L_COLOR:
			Serial.println("L_COLOR");
			setLColor(getNextColor(lColorType));
			break;
		case InputDevice::R_PLUS:
			Serial.println("R_PLUS");
			setRScore(rScore + 1);
			break;
		case InputDevice::R_MINUS:
			Serial.println("R_MINUS");
			setRScore(rScore - 1);
			break;
		case InputDevice::R_COLOR:
			Serial.println("R_COLOR");
			setRColor(getNextColor(rColorType));
			break;
		case InputDevice::RESET:
			Serial.println("RESET");
			display.setPixel(70, Color());
			display.setPixel(71, Color());
			setLScore(0);
			setRScore(0);
			setLColor(Color::WHITE);
			setRColor(Color::WHITE);
			break;
		}
		delay(10);
	}
	return std::make_shared<SleepState>(cfg);
}

void ShowScoreOfflineState::setLScore(int newScore) {
	lScore = min(99, max(0, newScore));
	display.showNumber(lScore, lColor, 0);
}
void ShowScoreOfflineState::setRScore(int newScore)
{
	rScore = min(99, max(0, newScore));
	display.showNumber(rScore, rColor, 72);
}

void ShowScoreOfflineState::setLColor(Color::ColorType newColor)
{
	lColorType = newColor;
	lColor = Color(newColor);
	display.showNumber(lScore, lColor, 0);
}

void ShowScoreOfflineState::setRColor(Color::ColorType newColor)
{
	rColorType = newColor;
	rColor = Color(newColor);
	display.showNumber(rScore, rColor, 72);
}

Color::ColorType ShowScoreOfflineState::getNextColor(Color::ColorType type)
{
	int newType = (((int) type) + 1) % (int) Color::NUM_COLORS;
	return Color::ColorType(newType);
}
