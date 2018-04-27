#include "ServerInOut.h"
String ssid1 =
#include "ssid1.h"
;
String pwd1 =
#include "pwd1.h"
;
String ssid2 =
#include "ssid2.h"
;
String pwd2 =
#include "pwd2.h"
;
String ssid3 =
#include "ssid3.h"
;
String pwd3 =
#include "pwd3.h"
;


String ServerInOut::sendRequest(String method, String url, String payload)
{
	String received;
	https.begin(url, fingerprint);
	https.addHeader("Accept", "application/json", true);
	https.addHeader("Authorization", "Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjRlNDE3Yjg3NGNkYzQ3YTdhNzA4ODE1OGIwZTBmZDY3MDc2MWIyYTc1OGQyODRhOTU3YTJjMjViMTIzNzk3MzRmZWZhMGU4NzQ0ZmQwNmNlIn0.eyJhdWQiOiI0IiwianRpIjoiNGU0MTdiODc0Y2RjNDdhN2E3MDg4MTU4YjBlMGZkNjcwNzYxYjJhNzU4ZDI4NGE5NTdhMmMyNWIxMjM3OTczNGZlZmEwZTg3NDRmZDA2Y2UiLCJpYXQiOjE1MjI4NzU3MjYsIm5iZiI6MTUyMjg3NTcyNiwiZXhwIjoxNTU0NDExNzI2LCJzdWIiOiIxMyIsInNjb3BlcyI6W119.eOS0o2mM03I-di8mNW9fO2NRsxpXoC_yj5akmV6AnAVF0yfzHnstWIhC0X8pKgeE7_kHsWc3TGS6rtu_BiUuIk48jlrpFHWOUWGuLpZPRRjcgqkqOqsWX6q97juAdUcBBDwJmdamWDy_XQ7xTqGd5qLAQtKSDJFDgVLjNnk7Y7w5j4lwY9bwhoxjELPBisb1WwCRDaAydOf1QoZPBe-p2xfNb87EK1jTqiYKO_bJGo54JW-a_5359_RQr3-3pVn8KP_tzZuPyyZHGBJh-ioLkYJ_bPjN_oTwOYVZslF_fppx4wXPBmBgiOa4XYRjSxiO5r7P1pwdrpDx8SClbcZw78XRW8R79K-tp-ofsZAiNxfl80ShWVjJ4P7z4IX6e-Z5zYQEjgAIRhPkfONsntESLS3fvwdX_RO6Ne203iot74IjmMHKR2OfIKerCxEs8_5o_ZtgDkrkqRljtKKBruAbpBNa2xwSCEIk7uiQu7WWbZL24mMakpNNpWorMxc1PeOcHu0SMhWXRW6glhHBfOwDZLHOp-JSkcd4okImc_z5Oga0N17C25XFEgFjii1lO7FRFvtcexCn88CXFzHqLTIOtYYYb_a_PktftKBgSjjwXr2GWcEKVddErXlwYp3DeIKdbt1p6UFcoAMHB21PeEiRnpLo_hYvqXG3MWXS4e8OCmk");
	https.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
	int httpCode = https.sendRequest(method.c_str(), payload);
	if (httpCode > 0) {
		received = https.getString();
	}
	else {
		Serial.printf("HTTP error: %s\n", https.errorToString(httpCode).c_str());
	}
	https.end();
	return received;
}
ServerInOut::ServerInOut()
{
	wifi.addAP(ssid1.c_str(), pwd1.c_str());
	wifi.addAP(ssid2.c_str(), pwd2.c_str());
	wifi.addAP(ssid3.c_str(), pwd3.c_str());
	Serial.println("Connecting ...");
	int i = 0;
	while (wifi.run() != WL_CONNECTED) {
		delay(500);
		Serial.print('.');
	}
	Serial.println();
	Serial.println("Connected to " + WiFi.SSID());
	fingerprint = "2d3be5152d49d30d0923f1cf7bebb90d20ea0723";
	https.addHeader("Accept", "application/json", true);
	https.addHeader("Authorization", "Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjRlNDE3Yjg3NGNkYzQ3YTdhNzA4ODE1OGIwZTBmZDY3MDc2MWIyYTc1OGQyODRhOTU3YTJjMjViMTIzNzk3MzRmZWZhMGU4NzQ0ZmQwNmNlIn0.eyJhdWQiOiI0IiwianRpIjoiNGU0MTdiODc0Y2RjNDdhN2E3MDg4MTU4YjBlMGZkNjcwNzYxYjJhNzU4ZDI4NGE5NTdhMmMyNWIxMjM3OTczNGZlZmEwZTg3NDRmZDA2Y2UiLCJpYXQiOjE1MjI4NzU3MjYsIm5iZiI6MTUyMjg3NTcyNiwiZXhwIjoxNTU0NDExNzI2LCJzdWIiOiIxMyIsInNjb3BlcyI6W119.eOS0o2mM03I-di8mNW9fO2NRsxpXoC_yj5akmV6AnAVF0yfzHnstWIhC0X8pKgeE7_kHsWc3TGS6rtu_BiUuIk48jlrpFHWOUWGuLpZPRRjcgqkqOqsWX6q97juAdUcBBDwJmdamWDy_XQ7xTqGd5qLAQtKSDJFDgVLjNnk7Y7w5j4lwY9bwhoxjELPBisb1WwCRDaAydOf1QoZPBe-p2xfNb87EK1jTqiYKO_bJGo54JW-a_5359_RQr3-3pVn8KP_tzZuPyyZHGBJh-ioLkYJ_bPjN_oTwOYVZslF_fppx4wXPBmBgiOa4XYRjSxiO5r7P1pwdrpDx8SClbcZw78XRW8R79K-tp-ofsZAiNxfl80ShWVjJ4P7z4IX6e-Z5zYQEjgAIRhPkfONsntESLS3fvwdX_RO6Ne203iot74IjmMHKR2OfIKerCxEs8_5o_ZtgDkrkqRljtKKBruAbpBNa2xwSCEIk7uiQu7WWbZL24mMakpNNpWorMxc1PeOcHu0SMhWXRW6glhHBfOwDZLHOp-JSkcd4okImc_z5Oga0N17C25XFEgFjii1lO7FRFvtcexCn88CXFzHqLTIOtYYYb_a_PktftKBgSjjwXr2GWcEKVddErXlwYp3DeIKdbt1p6UFcoAMHB21PeEiRnpLo_hYvqXG3MWXS4e8OCmk");
	https.addHeader("Content-Type", "application/x-www-form-urlencoded");
	
}


std::vector<std::shared_ptr<Color>> ServerInOut::getColorList(JsonArray &arr) const
{
	using namespace std;
	vector<std::shared_ptr<Color>> colors;
	for (int i = 0; i < arr.size(); ++i)
	{
		JsonObject &colorObj = arr[i].asObject();
		int r = String(colorObj["red"].asString()).toInt();
		int g = String(colorObj["green"].asString()).toInt();
		int b = String(colorObj["blue"].asString()).toInt();
		colors.push_back(make_shared<Color>(r, g, b));
	}
	return colors;
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
	String prev1(data.score1);
	String prev2(data.score2);
	String cur1(score1);
	String cur2(score2);
	data.score1 = score1;
	data.score2 = score2;
	String payload = "score1=" + cur1 + "&score2=" + cur2 + "&previousScore1=" + prev1 + "&previousScore2=" + prev2;
	String response = sendRequest("PATCH", updateScoreUrl, payload);
	DynamicJsonBuffer buffer;
	JsonObject &obj = buffer.parseObject(response);
	int score1_ = String(obj["score1"].asString()).toInt();
	int score2_ = String(obj["score2"].asString()).toInt();
	return (score1 == score1_) && (score2 == score2_); // return if server score matches local score
}

bool ServerInOut::updateSettings(int colorIndex1, int colorIndex2, bool swappedSides)
{
	String strColor1(colorIndex1);
	String strColor2(colorIndex2);
	String strSwapped(swappedSides);
	String payload = "colorIndex1=" + strColor1 +
		"&colorIndex2=" + strColor2 +
		"&swappedSides=" + strSwapped;
	String response = sendRequest("PATCH", updateSettingsUrl, payload);
	DynamicJsonBuffer buffer;
	JsonObject &obj = buffer.parseObject(response);
	data.colorIndex1 = String(obj["colorIndex1"].asString()).toInt();
	data.colorIndex2 = String(obj["colorIndex2"].asString()).toInt();
	bool swappedReceived= String(obj["swappedSides"].asString()).toInt();
	data.swappedSides = swappedSides;
}

ScoreboardData ServerInOut::loadConfig()
{
	ScoreboardData retval;
	String url = "https://playground.fackelup.de/api/scoreboards/me";
	String response = sendRequest("GET", url);
	DynamicJsonBuffer buffer;
	JsonObject &obj = buffer.parseObject(response);
	auto &gameObj = obj["game"].asObject();
	updateScoreUrl = gameObj["updateScore"].asObject()["href"].asString();
	updateSettingsUrl = obj["updateSettings"].asObject()["href"].asString();
	int colorIndex1 = String(obj["colorIndex1"].asString()).toInt();
	int colorIndex2 = String(obj["colorIndex2"].asString()).toInt();
	
	// update team colors
	retval.colorList1 = getColorList(gameObj["team1"].asObject()["colors"].asArray());
	retval.colorList2 = getColorList(gameObj["team2"].asObject()["colors"].asArray());
	retval.colorIndex1 = String(obj["colorIndex1"].asString()).toInt();
	retval.colorIndex2 = String(obj["colorIndex2"].asString()).toInt();
	retval.swappedSides = String(obj["swappedSides"].asString()).toInt();
	String score1 = gameObj["team1"].asObject()["score"].asString();
	String score2 = gameObj["team2"].asObject()["score"].asString();
	retval.score1 = score1.toInt();
	retval.score2 = score2.toInt();
	return retval;
}
