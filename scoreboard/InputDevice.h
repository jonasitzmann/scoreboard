#pragma once
#include <Arduino.h>
class InputDevice
{
public:
	enum Input {
		NO_INPUT,
		L_PLUS,
		L_MINUS,
		R_PLUS,
		R_MINUS,
		RESET,
		END
	};
	InputDevice();
	virtual ~InputDevice();
	virtual Input getInput() = 0;
};

class SerialInput : public InputDevice {
public:
	virtual InputDevice::Input getInput();
};
