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
	pinVals.push_back({ D1, false });
	pinVals.push_back({ D2, false });
	pinVals.push_back({ D3, false });
	pinVals.push_back({ D4, false });
	for_each(begin(pinVals), end(pinVals), [&](pair<int, bool> pinVal)
	{
		pinMode(pinVal.first, INPUT_PULLUP);
	});
}

std::vector<InputDevice::Input> ButtonInput::getInput()
{
	bool anyButtonPressed = updateButtonValues();
	if (anyButtonPressed)
		return {};
	int inputCode = calcInputCode();
	if (inputCode == NO_INPUT)
		return {};
	auto input = static_cast<InputDevice::Input>(inputCode);
	vector<InputDevice::Input> inputs;
	inputs.push_back(input);
	return inputs;
}

bool ButtonInput::updateButtonValues()
{
	bool anyPressed = false;
	for(auto itr = begin(pinVals); itr != end(pinVals); ++itr)
	{
		bool pressed = (digitalRead(itr->first) == LOW);
		anyPressed |= pressed;
		itr->second = itr->second || pressed;
	}
	return anyPressed;
}

int ButtonInput::calcInputCode()
{
	int inputCode = 0;
	int digit = 0;
	for (auto itr = begin(pinVals); itr != end(pinVals); ++itr)
	{
		if (itr->second) {
			inputCode += pow(2, digit);
			itr->second = false;
		}
		++digit;
	}
	return inputCode;
}
