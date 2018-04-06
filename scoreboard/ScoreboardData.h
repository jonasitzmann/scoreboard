#pragma once
#include "Color.h"
struct ScoreboardData {
	int lScore, rScore = 0;
	Color lColor, rColor;
	int trust = -1; // indicates if this data set is a dummy (-1) or approved from a trusted server (high number)
};