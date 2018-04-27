#include "ScoreboardData.h"
String ScoreboardData::toString() const
{
	String retval;
	retval += "score: " + String(score1) + ":" + String(score2) + "\n";
	retval += "color1: " + colorList1[colorIndex1]->toString() + "\n";
	retval += "color2: " + colorList2[colorIndex2]->toString() + "\n";
	retval += "swappedSides: " + String(swappedSides) + "\n";
	retval += "locked: " + locked ? "true" : "false";
	return retval;
}
