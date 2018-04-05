#pragma once
#include "Color.h"
#include "LedDisplay.h"
class OutputDevice
{
protected:
	int rScore, lScore = 0;
	Color rColor, lColor;
public:
	virtual void update() = 0;
	virtual bool updateRScore(int newScore) = 0;
	virtual bool updateLScore(int newScore) = 0;
	virtual bool updateRColor(Color newColor) = 0;
	virtual bool updateLColor(Color newColor) = 0;
	virtual bool updateAll(
		int rScore,
		int lScore,
		Color rColor,
		Color lColor
	) = 0;
};

class LedOutput : public OutputDevice
{
public:
	LedDisplay leds;
public:
	LedOutput();
	virtual void update();
	virtual bool updateRScore(int newScore);
	virtual bool updateLScore(int newScore);
	virtual bool updateRColor(Color newColor);
	virtual bool updateLColor(Color newColor);
	virtual bool updateAll(
		int rScore_,
		int lScore_,
		Color rColor_,
		Color lColor_
	);
};
