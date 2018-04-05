#include "ServerOutput.h"
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



String ServerOutput::sendRequest(String method, String url, String payload)
{
	https.begin(url, fingerprint);
	https.addHeader("Accept", "application/json", true);
	https.addHeader("Authorization", "Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjRlNDE3Yjg3NGNkYzQ3YTdhNzA4ODE1OGIwZTBmZDY3MDc2MWIyYTc1OGQyODRhOTU3YTJjMjViMTIzNzk3MzRmZWZhMGU4NzQ0ZmQwNmNlIn0.eyJhdWQiOiI0IiwianRpIjoiNGU0MTdiODc0Y2RjNDdhN2E3MDg4MTU4YjBlMGZkNjcwNzYxYjJhNzU4ZDI4NGE5NTdhMmMyNWIxMjM3OTczNGZlZmEwZTg3NDRmZDA2Y2UiLCJpYXQiOjE1MjI4NzU3MjYsIm5iZiI6MTUyMjg3NTcyNiwiZXhwIjoxNTU0NDExNzI2LCJzdWIiOiIxMyIsInNjb3BlcyI6W119.eOS0o2mM03I-di8mNW9fO2NRsxpXoC_yj5akmV6AnAVF0yfzHnstWIhC0X8pKgeE7_kHsWc3TGS6rtu_BiUuIk48jlrpFHWOUWGuLpZPRRjcgqkqOqsWX6q97juAdUcBBDwJmdamWDy_XQ7xTqGd5qLAQtKSDJFDgVLjNnk7Y7w5j4lwY9bwhoxjELPBisb1WwCRDaAydOf1QoZPBe-p2xfNb87EK1jTqiYKO_bJGo54JW-a_5359_RQr3-3pVn8KP_tzZuPyyZHGBJh-ioLkYJ_bPjN_oTwOYVZslF_fppx4wXPBmBgiOa4XYRjSxiO5r7P1pwdrpDx8SClbcZw78XRW8R79K-tp-ofsZAiNxfl80ShWVjJ4P7z4IX6e-Z5zYQEjgAIRhPkfONsntESLS3fvwdX_RO6Ne203iot74IjmMHKR2OfIKerCxEs8_5o_ZtgDkrkqRljtKKBruAbpBNa2xwSCEIk7uiQu7WWbZL24mMakpNNpWorMxc1PeOcHu0SMhWXRW6glhHBfOwDZLHOp-JSkcd4okImc_z5Oga0N17C25XFEgFjii1lO7FRFvtcexCn88CXFzHqLTIOtYYYb_a_PktftKBgSjjwXr2GWcEKVddErXlwYp3DeIKdbt1p6UFcoAMHB21PeEiRnpLo_hYvqXG3MWXS4e8OCmk");
	https.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
	int httpCode = https.sendRequest(method.c_str(), payload);
	if (httpCode > 0) {
		String received = https.getString();
		DynamicJsonBuffer buffer;
		JsonObject& obj = buffer.parseObject(received);
		int score1 = String(obj["score1"].asString()).toInt();
		int score2 = String(obj["score2"].asString()).toInt();
		Serial.printf("new score: %d : %d\n", score1, score2);

	}
	else {
		Serial.printf("HTTP error: %s\n", https.errorToString(httpCode).c_str());
	}
	https.end();
}

ServerOutput::ServerOutput()
{
	//ToDo: get current game id
	wifi.addAP(ssid1.c_str(), pwd1.c_str());
	wifi.addAP(ssid2.c_str(), pwd2.c_str());
	Serial.println("Connecting ...");
	int i = 0;
	while (wifi.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
		delay(1000);
		Serial.print('.');
	}
	Serial.println('\n');
	Serial.print("Connected to ");
	Serial.println(WiFi.SSID());
	Serial.println();
	// configure traged server and url
	fingerprint = "2d3be5152d49d30d0923f1cf7bebb90d20ea0723";
	https.addHeader("Accept", "application/json", true);
	https.addHeader("Authorization", "Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjRlNDE3Yjg3NGNkYzQ3YTdhNzA4ODE1OGIwZTBmZDY3MDc2MWIyYTc1OGQyODRhOTU3YTJjMjViMTIzNzk3MzRmZWZhMGU4NzQ0ZmQwNmNlIn0.eyJhdWQiOiI0IiwianRpIjoiNGU0MTdiODc0Y2RjNDdhN2E3MDg4MTU4YjBlMGZkNjcwNzYxYjJhNzU4ZDI4NGE5NTdhMmMyNWIxMjM3OTczNGZlZmEwZTg3NDRmZDA2Y2UiLCJpYXQiOjE1MjI4NzU3MjYsIm5iZiI6MTUyMjg3NTcyNiwiZXhwIjoxNTU0NDExNzI2LCJzdWIiOiIxMyIsInNjb3BlcyI6W119.eOS0o2mM03I-di8mNW9fO2NRsxpXoC_yj5akmV6AnAVF0yfzHnstWIhC0X8pKgeE7_kHsWc3TGS6rtu_BiUuIk48jlrpFHWOUWGuLpZPRRjcgqkqOqsWX6q97juAdUcBBDwJmdamWDy_XQ7xTqGd5qLAQtKSDJFDgVLjNnk7Y7w5j4lwY9bwhoxjELPBisb1WwCRDaAydOf1QoZPBe-p2xfNb87EK1jTqiYKO_bJGo54JW-a_5359_RQr3-3pVn8KP_tzZuPyyZHGBJh-ioLkYJ_bPjN_oTwOYVZslF_fppx4wXPBmBgiOa4XYRjSxiO5r7P1pwdrpDx8SClbcZw78XRW8R79K-tp-ofsZAiNxfl80ShWVjJ4P7z4IX6e-Z5zYQEjgAIRhPkfONsntESLS3fvwdX_RO6Ne203iot74IjmMHKR2OfIKerCxEs8_5o_ZtgDkrkqRljtKKBruAbpBNa2xwSCEIk7uiQu7WWbZL24mMakpNNpWorMxc1PeOcHu0SMhWXRW6glhHBfOwDZLHOp-JSkcd4okImc_z5Oga0N17C25XFEgFjii1lO7FRFvtcexCn88CXFzHqLTIOtYYYb_a_PktftKBgSjjwXr2GWcEKVddErXlwYp3DeIKdbt1p6UFcoAMHB21PeEiRnpLo_hYvqXG3MWXS4e8OCmk");
	https.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
}


ServerOutput::~ServerOutput()
{
}

void ServerOutput::update()
{
}

bool ServerOutput::updateRScore(int newScore)
{
	updateAll(newScore, lScore, rColor, lColor);
	return false;
}

bool ServerOutput::updateLScore(int newScore)
{
	updateAll(rScore, newScore, rColor, lColor);
	return false;
}

bool ServerOutput::updateRColor(Color newColor)
{
	updateAll(rScore, lScore, newColor, lColor);
	return false;
}

bool ServerOutput::updateLColor(Color newColor)
{
	updateAll(rScore, lScore, rColor, newColor);
	return false;
}

bool ServerOutput::updateAll(int rScore_, int lScore_, Color rColor_, Color lColor_)
{
	String prev1(lScore);
	String prev2(rScore);
	String cur1(lScore_);
	String cur2(rScore_);
	rScore = rScore_;
	lScore = lScore_;
	rColor = rColor_;
	lColor = lColor_;
	String payload = "score1=" + cur1 + "&score2=" + cur2 + "&previousScore1=" + prev1 + "&previousScore2=" + prev2;
	sendRequest("PATCH", "https://playground.fackelup.de/api/games/25/score", payload);
	return false;
}
