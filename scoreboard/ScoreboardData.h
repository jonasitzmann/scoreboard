#pragma once
#include "Color.h"
#include <vector>
#include <memory>
using namespace std;
struct ScoreboardData {
	ScoreboardData();
	vector<shared_ptr<Color>> colorList1, colorList2;
	int score1, score2;
	int colorIndex1, colorIndex2;
    bool swappedSides, scoreIsFinal = false;
	int trust = -1; // indicates if this data set is a dummy (-1) or approved from a trusted server (high number)
	String toString();
};
