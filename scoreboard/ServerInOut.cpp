#include "ServerInOut.h"
#include "utils.h"
#include <stdlib.h>

std::vector<std::shared_ptr<Color>> ServerInOut::getColorList(JsonArray &arr) const
{
	using namespace std;
	vector<std::shared_ptr<Color>> colors;
	for (int i = 0; i < arr.size(); ++i)
	{
		JsonObject &colorObj = arr[i].asObject();
		int r = atoi(colorObj["red"].asString());
		int g = atoi(colorObj["green"].asString());
		int b = atoi(colorObj["blue"].asString());
		colors.push_back(make_shared<Color>(r, g, b));
	}
	return colors;
}

ServerInOut::ServerInOut(std::shared_ptr<ILogger> logger, std::shared_ptr<IWiFi> wifi, std::shared_ptr<IHttpClient> https):
	logger(logger),
	wifi(wifi),
	https(https)
{
	wifi->begin();
	https->begin();
}

bool ServerInOut::update(ScoreboardData newData)
{
	bool scoreChanged = (data.score1 != newData.score1) ||
						(data.score2 != newData.score2);
	bool settingsChanged = (data.colorIndex1 != newData.colorIndex1) ||
		(data.colorIndex2 != newData.colorIndex2) ||
		(data.swappedSides != newData.swappedSides);
	bool scoreConsistent = true;
	if (scoreChanged)
	{
		bool b1 = updateScores(newData.score1, newData.score2);
		scoreConsistent &= b1;
	}
	if (!scoreConsistent)
	{
		return false;
	}
	data = newData;
	if (settingsChanged)
	{
		updateSettings(data.colorIndex1, data.colorIndex2, data.swappedSides);
	}
	return true;
}

bool ServerInOut::updateScores(int score1, int score2)
{
	std::string prev1(int2Str(data.score1));
	std::string prev2(int2Str(data.score2));
	std::string cur1(int2Str(score1));
	std::string cur2(int2Str(score2));
	data.score1 = score1;
	data.score2 = score2;
	std::string payload = "score1=" + cur1 + "&score2=" + cur2 + "&previousScore1=" + prev1 + "&previousScore2=" + prev2;
	std::string response = https->sendRequest("PATCH", updateScoreUrl, payload);
	DynamicJsonBuffer buffer;
	JsonObject &obj = buffer.parseObject(response.c_str());
	int score1_ = atoi(obj["score1"].asString());
	int score2_ = atoi(obj["score2"].asString());
	return (score1 == score1_) && (score2 == score2_); // return if server score matches local score
}

bool ServerInOut::updateSettings(int colorIndex1, int colorIndex2, bool swappedSides)
{
	std::string strColor1(int2Str(colorIndex1));
	std::string strColor2(int2Str(colorIndex2));
	std::string strSwapped(int2Str(swappedSides));
	std::string payload = "colorIndex1=" + strColor1 +
		"&colorIndex2=" + strColor2 +
		"&swappedSides=" + strSwapped;
	std::string response = https->sendRequest("PATCH", updateSettingsUrl, payload);
	DynamicJsonBuffer buffer;
	JsonObject &obj = buffer.parseObject(response.c_str());
	data.colorIndex1 = atoi(obj["colorIndex1"].asString());
	data.colorIndex2 = atoi(obj["colorIndex2"].asString());
	bool swappedReceived = atoi(obj["swappedSides"].asString());
	data.swappedSides = swappedSides;
}

ScoreboardData ServerInOut::loadConfig()
{
	ScoreboardData retval;
	std::string url = "https://playground.fackelup.de/api/scoreboards/me";
	std::string response = https->sendRequest("GET", url);
	DynamicJsonBuffer buffer;
	JsonObject &obj = buffer.parseObject(response.c_str());
	auto &gameObj = obj["game"].asObject();
	updateScoreUrl = gameObj["updateScore"].asObject()["href"].asString();
	updateSettingsUrl = obj["updateSettings"].asObject()["href"].asString();
	int colorIndex1 = atoi(obj["colorIndex1"].asString());
	int colorIndex2 = atoi(obj["colorIndex2"].asString());
	
	// update team colors
	retval.colorList1 = getColorList(gameObj["team1"].asObject()["colors"].asArray());
	retval.colorList2 = getColorList(gameObj["team2"].asObject()["colors"].asArray());
	retval.colorIndex1 = atoi(obj["colorIndex1"].asString());
	retval.colorIndex2 = atoi(obj["colorIndex2"].asString());
	retval.swappedSides = atoi(obj["swappedSides"].asString());
	retval.score1 = atoi(gameObj["team1"].asObject()["score"].asString());
	retval.score2 = atoi(gameObj["team2"].asObject()["score"].asString());
	return retval;
}
