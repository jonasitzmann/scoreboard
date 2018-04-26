#pragma once
#include <Arduino.h>
#include <map>
#include "ScoreboardData.h"
#include <pcf8574_esp.h>
#include <Wire.h>
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
		LOCK,
		RESET,
		SWAP,
		UNLOCK
	};
	virtual std::vector<Input> getInput() = 0;

};

class SerialInput : public InputDevice {
public:
	SerialInput();
	virtual std::vector<Input> getInput();
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
	vector<pair<int, bool>> pinVals;
	bool updateButtonValues();
	int calcInputCode();
public:
	ButtonInput();
	virtual std::vector<Input> getInput();
};