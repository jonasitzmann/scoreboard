#include "ScoreboardData.h"
#include "utils.h"
std::string ScoreboardData::toString() const
{
	std::string retval;
	retval += "score: " + int2Str(score1) + ":" + int2Str(score2) + "\n";
	retval += "color1: " + colorList1[colorIndex1]->toString() + "\n";
	retval += "color2: " + colorList2[colorIndex2]->toString() + "\n";
	retval += "swappedSides: " + int2Str(swappedSides) + "\n";
	retval += "locked: " + locked ? "true" : "false";
	return retval;
}
