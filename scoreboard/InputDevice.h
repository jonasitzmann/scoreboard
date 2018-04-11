#pragma once
#include <Arduino.h>
#include <map>
#include "ScoreboardData.h"
class InputDevice
{
public:
	enum Input {
		NO_INPUT,
		L_COLOR,
		L_PLUS,
		L_MINUS,
		R_COLOR,
		R_PLUS,
		R_MINUS,
		END,
		RESET,
		SWAP,
		RESUME
	};
	InputDevice();
	virtual ~InputDevice();
	virtual Input getInput() = 0;
	virtual ScoreboardData init() = 0;
};

class SerialInput : public InputDevice {
public:
	SerialInput();
	virtual InputDevice::Input getInput();
	virtual ScoreboardData init();
};

struct CmpPins {
	static int gpio2Pin(const int& val) {
		switch (val) {
		case D0: return 0;
		case D1: return 1;
		case D2: return 2;
		case D3: return 3;
		case D4: return 4;
		case D5: return 5;
		case D6: return 6;
		case D7: return 7;
		case D8: return 8;
		case D9: return 9;
		case D10: return 10;

		default: return -1;
		}
	}
	bool operator() (const int &lhs, const int &rhs) {
		return gpio2Pin(lhs) < gpio2Pin(rhs);
	}
};

class ButtonInput : public InputDevice {
	std::map<int, bool, CmpPins> pinValues = {
		{ D1, true },
		{ D2, true },
		{ D3, true },
		{ D4, true }
	};
public:
	ButtonInput();
	virtual InputDevice::Input getInput();
	virtual ScoreboardData init();
};