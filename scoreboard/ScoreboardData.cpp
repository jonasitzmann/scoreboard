#include "ScoreboardData.h"
String ScoreboardData::toString() const
{
	String retval;
	retval += "Score: " + String(score1) + ":" + String(score2) + "\n";
	retval += "Color1: " + colorList1[colorIndex1]->toString() + "\n";
	retval += "Color2: " + colorList2[colorIndex2]->toString() + "\n";
	retval += "SwappedSides: " + String(swappedSides);
	return retval;
}
