#pragma once
#include "Color.h"
#include <vector>
#include <memory>
#include <string>
using namespace std;
struct ScoreboardData {
	vector<shared_ptr<Color>> colorList1, colorList2 = {};
	int score1 = 0, score2 = 0;
	int colorIndex1 = 0, colorIndex2 = 0;
    bool swappedSides = false, locked = false;
	std::string toString() const;
	ScoreboardData() {
		colorList1.push_back(make_shared<Color>());
		colorList2.push_back(make_shared<Color>());
	}
};
