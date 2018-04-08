#include "ScoreboardData.h"

String ScoreboardData::toString()
{
	String retval;
	retval += "Score: " + String(score1) + ":" + String(score2) + "\n";
	retval += "Color1: " + color1.toString() + "\n";
	retval += "Color2: " + color2.toString() + "\n";
	retval += "SwappedSides: " + String(swappedSides);
	return retval;
}
