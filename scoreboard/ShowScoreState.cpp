#include "StateMachine.h"


std::shared_ptr<State> ShowScoreState::handle()
{
	while (wfClient->connected()) {
		String data;
		wsClient->getData(data);
		if (data.length() > 0 && String(data.toInt()) == data) {
			setScore(data.toInt());
		}
		else if (data == "incr") {
			setScore(score + 1);
		}
		else if (data == "decr") {
			setScore(score - 1);
		}
	}
	return std::make_shared<StartState>();
}

void ShowScoreState::setScore(int newScore) {
	score = newScore;
	display.showNumber(score, color);
}
void ShowScoreState::setColor(Color newColor) {
	color = newColor;
	display.showNumber(score, color);
}