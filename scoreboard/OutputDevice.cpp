#include "OutputDevice.h"

LedOutput::LedOutput(): leds(D5, 142, false)
{
	update();
}

void LedOutput::update()
{
	leds.showNumber(lScore, lColor, 0);
	leds.showNumber(rScore, rColor, 72);
	leds.setPixel(70, Color());
	leds.setPixel(71, Color());
	leds.show();
}

bool LedOutput::updateRScore(int newScore)
{
	rScore = newScore;
	update();
	return true;
}

bool LedOutput::updateLScore(int newScore)
{
	lScore = newScore;
	update();
	return true;
}

bool LedOutput::updateRColor(Color newColor)
{
	rColor = newColor;
	update();
	return true;
}

bool LedOutput::updateLColor(Color newColor)
{
	lColor = newColor;
	update();
	return true;
}

bool LedOutput::updateAll(int rScore_, int lScore_, Color rColor_, Color lColor_)
{
	rScore = rScore_;
	lScore = lScore_;
	rColor = rColor_;
	lColor = lColor_;
	update();
	return true;
}
