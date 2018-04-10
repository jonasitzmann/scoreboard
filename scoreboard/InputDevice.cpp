#include "InputDevice.h"


InputDevice::InputDevice()
{
}


InputDevice::~InputDevice()
{
}

SerialInput::SerialInput()
{
	Serial.setTimeout(10);
}

InputDevice::Input SerialInput::getInput()
{
	String serialStr = Serial.readString();
	if (serialStr.length() == 0) {
		return NO_INPUT;
	}
	if (serialStr == "lPlus()") return L_PLUS;
	else if (serialStr == "lMinus()") return L_MINUS;
	else if (serialStr == "rPlus()") return R_PLUS;
	else if (serialStr == "rMinus()") return R_MINUS;
	else if (serialStr == "reset()") return RESET;
	else if (serialStr == "end()") return END;
	return NO_INPUT;
}

ScoreboardData SerialInput::init()
{
	ScoreboardData retval;
	return retval;
}

ButtonInput::ButtonInput()
{
	for (auto itr = pinValues.begin(); itr != pinValues.end(); ++itr) {
		pinMode(itr->first, INPUT_PULLUP);
	}
}

InputDevice::Input ButtonInput::getInput()
{
	int inputCode = 0;
	bool anyPressed = false;
	// update buttonValues
	for (auto itr = pinValues.begin(); itr != pinValues.end(); ++itr) {
		bool pressed = digitalRead(itr->first) == LOW? true : false;
		anyPressed |= pressed;
		itr->second |= pressed;
	}
	if (!anyPressed) {
		delay(50);
		// calc inputCode from buttonValues
		int digit = 0;
		for (auto itr = pinValues.begin(); itr != pinValues.end(); ++itr) {
			if (itr->second) {
				inputCode += pow(2, digit);
				itr->second = false; // reset buttonValue
			}
			++digit;
		}
	}
	return static_cast<InputDevice::Input>(inputCode);
}

ScoreboardData ButtonInput::init()
{
	ScoreboardData retval;
	retval.colorIndex1 = 0;
	retval.colorIndex2 = 0;
	retval.score1 = 42;
	retval.score2 = 42;
	retval.trust = 1;
  retval.swappedSides = false;
	return retval;
}
