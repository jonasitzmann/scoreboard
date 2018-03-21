#include "InputDevice.h"



InputDevice::InputDevice()
{
}


InputDevice::~InputDevice()
{
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
