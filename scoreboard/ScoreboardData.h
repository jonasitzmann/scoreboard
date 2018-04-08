#pragma once
#include "Color.h"
struct ScoreboardData {
	int score1, score2 = 0;
	Color color1, color2;
    bool swappedSides = false;
	int trust = -1; // indicates if this data set is a dummy (-1) or approved from a trusted server (high number)
	String toString();
};
