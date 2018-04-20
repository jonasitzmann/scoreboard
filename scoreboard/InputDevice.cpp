#include "InputDevice.h"

SerialInput::SerialInput()
{
	Serial.setTimeout(10);
}

InputDevice::Input SerialInput::getInput() const
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

ButtonInput::ButtonInput()
{
	for_each(begin(pins), end(pins), [](int pin)
	{
		pinMode(pin, INPUT_PULLUP);
	});
}

InputDevice::Input ButtonInput::getInput() const
{
	std::map<int, bool, CmpPins> pinValues;
	for_each(begin(pins), end(pins), [&pinValues](int pin)
	{
		pinValues[pin] = false;
	});
	bool anyPressed = false;
	// update buttonValues
	for (auto itr = pinValues.begin(); itr != pinValues.end(); ++itr) {
		bool pressed = digitalRead(itr->first) == LOW ? true : false;
		anyPressed |= pressed;
		itr->second = pressed;
	}
	// calc inputCode from buttonValues
	int inputCode = 0;
	int digit = 0;
	for_each(begin(pinValues), end(pinValues), [&inputCode, &digit](pair<int, bool> pinVal) {
		if (pinVal.second) {
			inputCode += pow(2, digit);
			pinVal.second = false; // reset buttonValue
		}
		++digit;
	});

	return static_cast<InputDevice::Input>(inputCode);
}
