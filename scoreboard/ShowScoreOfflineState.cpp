#pragma once
#include "StateMachine.h"


String ShowScoreOfflineState::getName() {
	return "ShowScoreOfflineState";
}

void ShowScoreOfflineState::handleUpButton() {
	bool upButtonPressed = digitalRead(upPin);
	if (upButtonPressed && !upButtonPressedBefore) {
		setLScore(lScore + 1);
	}
	upButtonPressedBefore = upButtonPressed;
}

void ShowScoreOfflineState::handleDownButton() {
	bool downButtonPressed = digitalRead(downPin);
	if (downButtonPressed && !downButtonPressedBefore) {
		setLScore(lScore - 1);
	}
	downButtonPressedBefore = downButtonPressed;
}

void ShowScoreOfflineState::handleColorButton() {
	bool colorButtonPressed = digitalRead(colorPin);
	if (colorButtonPressed && !colorButtonPressedBefore) {
		Color newColor(BLACK);
		newColor.r = (lColor.r + 50) % 255;
		newColor.g = (lColor.g + 100) % 255;
		newColor.b = (lColor.b + 150) % 255;
		setLColor(newColor);
	}
	colorButtonPressedBefore = colorButtonPressed;
}

ShowScoreOfflineState::ShowScoreOfflineState(std::shared_ptr<Configuration> cfg) :
	lColor(RED),
	rColor(GREEN),
	lScore(0),
	rScore(0),
	upPin(D2), downPin(D1), colorPin(D3),
	colorButtonPressedBefore(false), upButtonPressedBefore(false), downButtonPressedBefore(false),
	display(D6, cfg->numPixels, true) // USE_EMULATOR HARD CODED
{
	inputDevice = new SerialInput();
}

std::shared_ptr<State> ShowScoreOfflineState::handle() {
	while (!(digitalRead(upPin) && digitalRead(downPin) && digitalRead(colorPin))) {
		//Serial.printf("up: %d ", digitalRead(upPin));
		//Serial.printf("down: %d ", digitalRead(downPin));
		//Serial.printf("color: %d\n", digitalRead(colorPin));
		//handleUpButton();
		//handleDownButton();
		//handleColorButton();
		auto input = inputDevice->getInput();
		switch (input) {
		case InputDevice::NO_INPUT:
			break;
		case InputDevice::L_PLUS:
			setLScore(lScore + 1);
			break;
		case InputDevice::L_MINUS:
			setLScore(lScore - 1);
			break;
		case InputDevice::R_PLUS:
			setRScore(rScore + 1);
			break;
		case InputDevice::R_MINUS:
			setRScore(rScore - 1);
			break;
		case InputDevice::RESET:
			setLScore(0);
			setRScore(0);
			break;
	}
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
	display.showNumber(rScore, rColor, 1);
}

void ShowScoreOfflineState::setLColor(Color newColor)
{
	lColor = newColor;
	display.showNumber(lScore, lColor, 0);
}

void ShowScoreOfflineState::setRColor(Color newColor)
{
	rColor = newColor;
	display.showNumber(rScore, rColor, 1);
}
