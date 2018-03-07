#pragma once
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "Configuration.h"

#define S(x) #x
#define STR(x) S(x)
extern String htmlForm;

class ConfigServer {
	std::shared_ptr<Configuration> cfg;
	const char* ssid = "scoreboard";
	const char* password = "scoreboard";
	ESP8266WebServer server;
	/*String htmlForm = "Input Box"
		"<!DOCTYPE HTML>"
		"	<form action = \"/results\" method = \"POST\">"
		"	SSID:<br>"
		"	<input type = \"text\" name = \"ssid\"><br>"
		"	Password : <br>"
		"	<input type = \"text\" name = \"pwd\"><br>"
		"	Host Ip : <br>"
		"	<input type = \"text\" name = \"ip\"><br>"
		"	Host Port : <br>"
		"	<input type = \"text\" name = \"port\"><br>"
		"	Id : <br>"
		"	<input type = \"text\" name = \"id\"><br>"
		"	Number of Pixels : <br>"
		"	<input type = \"text\" name = \"numPixels\"><br>"
		"	Emulate LEDs : <br>"
		"	<input type = \"text\" name = \"emulate\"><br>"
		"	Write : <input type = \"radio\" name = \"write\">"
		"	</br><input type = \"submit\" value = \"Save\"></form>";*/
public:
	bool configChanged;
	ConfigServer(std::shared_ptr<Configuration> cfg) : cfg(cfg), server(80), configChanged(false) {} // serve at port 80
	void handleRoot() {
		server.send(200, "text/html", htmlForm);
	}

	void handlePost() {
		// Post arguments are provided by server.arg("argName")
		if (server.hasArg("ssid") && server.arg("ssid") != "") {
			// copy arg to configuration
			cfg->ssid = server.arg("ssid");
			configChanged = true;
		}
		if (server.hasArg("pwd") && server.arg("pwd") != "") {
			cfg->password = server.arg("pwd");
			configChanged = true;
		}
		if (server.hasArg("ip") && server.arg("ip") != "") {
			cfg->hostIp = server.arg("ip");
			configChanged = true;
		}
		if (server.hasArg("port") && server.arg("port") != "") {
			cfg->hostPort = server.arg("port").toInt();
			configChanged = true;
		}
		if (server.hasArg("id") && server.arg("id") != "") {
			cfg->id = server.arg("id");
			configChanged = true;
		}
		if (server.hasArg("numPixels") && server.arg("numPixels") != "") {
			cfg->numPixels = server.arg("numPixels").toInt();
			configChanged = true;
		}
		if (server.hasArg("emulate") && server.arg("emulate") != "") {
			cfg->useEmulator = server.arg("emulate").toInt();
			configChanged = true;
		}
		if (server.hasArg("write")) {
			if (server.arg("write") == "on") {
				cfg->save(); //write config to EEPROM
			}
		}
		server.send(200, "text/html", "<h1>Hello World");
		Serial.println(cfg->ssid);
		Serial.println(cfg->password);
		Serial.println(cfg->hostIp);
		Serial.println(cfg->hostPort);
		Serial.println(cfg->id);
		Serial.println(cfg->numPixels);
		Serial.println(cfg->useEmulator);
	}

	void handleNotFound() {
		server.send(404, "text/plain", "404: Not found");
	}
	void start() {
		WiFi.mode(WIFI_AP); //Only Access point
		WiFi.softAP(ssid, password);  //Start Hotspot

		server.on("/", HTTP_GET, std::bind(&ConfigServer::handleRoot, this));
		server.on("/results", HTTP_POST, std::bind(&ConfigServer::handlePost, this));
		server.onNotFound(std::bind(&ConfigServer::handleNotFound, this));

		server.begin();
		// Print Server IP to Serial
		Serial.print("HTTP server started at ");
		IPAddress myIP = WiFi.softAPIP();
		Serial.println(myIP);
		configChanged = false;
	}
	void terminate() {
		WiFi.softAPdisconnect();
		WiFi.disconnect();
		WiFi.mode(WIFI_OFF);
	}
	std::shared_ptr<Configuration> updateConfig() {
		server.handleClient();
	}

};