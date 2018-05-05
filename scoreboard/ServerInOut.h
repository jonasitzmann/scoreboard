#pragma once
#include "ILogger.h"
#include "OutputDevice.h"
#include "InputDevice.h"
#include "IConfigLoader.h"
#include "ScoreboardData.h"
#include "IWiFi.h"
#include <ArduinoJson.h>
#include "IHttpClient.h"

class ServerInOut :
	public OutputDevice,
	public IConfigLoader
{
	std::shared_ptr<ILogger> logger;
	std::shared_ptr<IWiFi> wifi;
	std::shared_ptr<IHttpClient> https;
	std::string fingerprint;
	std::string updateScoreUrl;
	std::string updateSettingsUrl;
	bool updateSettings(int colorIndex1, int colorIndex2, bool swappedSides);
	bool updateScores(int score1, int score2);
	vector<shared_ptr<Color>> getColorList(JsonArray &arr) const;
public:
	ServerInOut(std::shared_ptr<ILogger> logger, std::shared_ptr<IWiFi> wifi, std::shared_ptr<IHttpClient> https);
	bool update(ScoreboardData newData) override;
	ScoreboardData loadConfig() override;
};

