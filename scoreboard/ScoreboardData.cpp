#include "ScoreboardData.h"

ScoreboardData::ScoreboardData(): score1(0), score2(0), colorIndex1(0), colorIndex2(0)
{
	for (Color::ColorType t = Color::WHITE; t != Color::NUM_COLORS; t = Color::ColorType(t + 1))
	{
		auto color = make_shared<Color>(t);
		colorList1.push_back(color);
		colorList2.push_back(color);
	}
}

String ScoreboardData::toString()
{
	String retval;
	retval += "Score: " + String(score1) + ":" + String(score2) + "\n";
	retval += "Color1: " + colorList1[colorIndex1]->toString() + "\n";
	retval += "Color2: " + colorList2[colorIndex2]->toString() + "\n";
	retval += "SwappedSides: " + String(swappedSides);
	return retval;
}
