#pragma once
#include "Color.h"
#include <vector>
#include <memory>
using namespace std;
struct ScoreboardData {
	vector<shared_ptr<Color>> colorList1, colorList2 = {make_shared<Color>()};
	int score1, score2 = 0;
	int colorIndex1, colorIndex2 = 0;
    bool swappedSides, scoreIsFinal = false;
	String toString() const;
};
