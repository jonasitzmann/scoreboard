#pragma once
#include "Color.h"
#include "LedDisplay.h"
#include "ScoreboardData.h"
class OutputDevice
{
protected:
	ScoreboardData data;
public:
	virtual bool update(ScoreboardData newData) = 0;
};

class LedOutput : public OutputDevice
{
public:
	LedDisplay leds;
public:
	bool update(ScoreboardData newData) override;
};
