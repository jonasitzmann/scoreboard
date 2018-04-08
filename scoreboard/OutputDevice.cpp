#include "OutputDevice.h"

LedOutput::LedOutput(): leds(D5, 142, false)
{
	update(data);
}

bool LedOutput::update(ScoreboardData newData)
{
	data = newData;
	if (!data.swappedSides)
	{
		leds.showNumber(data.score1, data.color1, 0);
		leds.showNumber(data.score2, data.color2, 72);
	}
	else
	{
		leds.showNumber(data.score1, data.color1, 0);
		leds.showNumber(data.score2, data.color2, 72);
	}

	leds.setPixel(70, Color());
	leds.setPixel(71, Color());
	leds.show();
	return true;
}