#include "OutputDevice.h"

LedOutput::LedOutput(): leds(D5, 142, false)
{
	update(data);
}

bool LedOutput::update(ScoreboardData newData)
{
	data = newData;
	int offset1 = data.swappedSides ? 72  : 0;
	int offset2 = data.swappedSides ? 0 : 72;
	shared_ptr<Color> color1 = data.colorList1[data.colorIndex1];
	shared_ptr<Color> color2 = data.colorList2[data.colorIndex2];

	leds.showNumber(data.score1, *color1, offset1);
	leds.showNumber(data.score2, *color2, offset2);

	leds.setPixel(70, Color());
	leds.setPixel(71, Color());
	leds.show();
	return true;
}
