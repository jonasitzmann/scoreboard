#include "InputDevice.h"
#include <map>

SerialInput::SerialInput()
{
	Serial.setTimeout(10);
}

std::vector<InputDevice::Input> SerialInput::getInput()
{
	using namespace std;
	vector<InputDevice::Input> inputs;
	String serialStr = Serial.readString();
	if (serialStr.length() == 0) {
		return inputs;
	}
	std::map<String, InputDevice::Input> string2Input = {
		{"lPlus", L_PLUS},
		{"lMinus", L_MINUS},
		{"rPlus", R_PLUS},
		{"rMinus", R_MINUS},
		{"rColor", R_COLOR},
		{"lColor", L_COLOR},
		{"swap", SWAP},
		{"reset", RESET},
		{"lock", LOCK},
		{"unlock", UNLOCK}
	};
	std::for_each(begin(string2Input), end(string2Input), [&](pair<String, Input> inputPair) {
		if (serialStr == inputPair.first)
		{
			inputs.push_back(inputPair.second);
		}
	});
	return inputs;
}

ButtonInput::ButtonInput()
{
	for_each(begin(pins), end(pins), [&](int pin)
	{
		pinMode(pin, INPUT_PULLUP);
		pinValues[pin] = false;
	});
}

std::vector<InputDevice::Input> ButtonInput::getInput()
{
	bool anyButtonPressed = updateButtonValues();
	if (anyButtonPressed)
	{
		return {};
	}
	int inputCode = calcInputCode();
	return vector<InputDevice::Input>(inputCode);
}

bool ButtonInput::updateButtonValues()
{
	bool anyPressed = true;
	for (auto itr = pinValues.begin(); itr != pinValues.end(); ++itr) {
		bool pressed = digitalRead(itr->first) == LOW ? true : false;
		anyPressed |= pressed;
		itr->second = pressed;
	}
	return anyPressed;
}

int ButtonInput::calcInputCode() const
{
	int inputCode = 0;
	int digit = 0;
	for_each(begin(pinValues), end(pinValues), [&](pair<int, bool> pinVal) {
		if (pinVal.second) {
			inputCode += pow(2, digit);
			pinVal.second = false; // reset buttonValue
		}
		++digit;
	});
}
