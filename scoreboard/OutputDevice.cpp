#include "OutputDevice.h"

bool LedOutput::update(ScoreboardData newData)
{
	data = newData;
	Serial.println("update leds: \n" + data.toString());
	int offset1 = 0;
	int offset2 = 72;
	if (data.swappedSides)
		swap<int>(offset1, offset2);
	shared_ptr<Color> color1 = data.colorList1[data.colorIndex1];
	shared_ptr<Color> color2 = data.colorList2[data.colorIndex2];

	leds.showNumber(data.score1, *color1, offset1);
	leds.showNumber(data.score2, *color2, offset2);

	// the colon to separate the two scores
	leds.setPixel(70, Color());
	leds.setPixel(71, Color());

	leds.show();
	return true;
}
