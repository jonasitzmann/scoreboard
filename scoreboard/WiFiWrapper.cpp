#include "Arduino.h"
#include "WiFiWrapper.h"


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






WiFiWrapper::WiFiWrapper():
	logger(LoggerFactory::getLogger())
{
	wifi.addAP(ssid1.c_str(), pwd1.c_str());
	wifi.addAP(ssid2.c_str(), pwd2.c_str());
	wifi.addAP(ssid3.c_str(), pwd3.c_str());
}

bool WiFiWrapper::begin()
{
	logger.log("Connecting ...");
	int i = 0;
	while (wifi.run() != WL_CONNECTED) {
		delay(500);
		logger.log(".");
		++i;
		if (i == 10)
		{
			return false;
		}
	}
	logger.log("");
	std::string ssid(WiFi.SSID().c_str());
	logger.log("Connected to " + ssid);
	return true;
}
