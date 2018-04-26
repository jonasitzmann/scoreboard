#pragma once
#include "OutputDevice.h"
#include "InputDevice.h"
#include "IConfigLoader.h"
#include "ScoreboardData.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <JsonStreamingParser.h>
#define S(x) #x
#define STR(x) S(x)
extern String ssid1;
extern String ssid2;
extern String pwd1;
extern String pwd2;
class ServerInOut :
	public OutputDevice,
	public IConfigLoader
{
	ESP8266WiFiMulti wifi;
	HTTPClient https;
	String fingerprint;
	String updateScoreUrl;
	String updateSettingsUrl;
	String sendRequest(String method, String url, String payload = "");
	bool updateSettings(int colorIndex1, int colorIndex2, bool swappedSides);
	bool updateScores(int score1, int score2);
	vector<shared_ptr<Color>> getColorList(JsonArray &arr) const;
public:
	ServerInOut();
	bool update(ScoreboardData newData) override;
	ScoreboardData loadConfig() override;
};

