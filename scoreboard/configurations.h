	#include <EEPROM.h>
	#include <string.h>
/*
ssid = "EasyBox-522111"
hostIp = "192.168.2.112"
password = ""
hostPort = 8000
numPixels = 70
useEmulator = true
id = "Scoreboard1"
;*/
	static const int CONFIG_BEGIN = 0;
	class ScoreboardConfiguration {
		typedef struct {
			char id[30];
			char ssid[30];
			char password[30];
			char hostIp[30];
			int hostPort;
			bool useEmulator;
			int numPixels;
		} config_t;
	public:
		char* id;
		char* ssid;
		char* password;
		char* hostIp;
		int hostPort;
		bool useEmulator;
		int numPixels;
		void load() {
			EEPROM.begin(4095);
			EEPROM.get(CONFIG_BEGIN, m_config);
			delay(50);
			EEPROM.end();
			id = &m_config.id[0];
			ssid = &m_config.ssid[0];
			password = &m_config.password[0];
			hostIp = &m_config.hostIp[0];
			hostPort = m_config.hostPort;
			useEmulator = m_config.useEmulator;
			numPixels = m_config.numPixels;
		}
		void save() {
			strncpy(m_config.id, id, sizeof m_config.id);
			strncpy(m_config.ssid, ssid, sizeof m_config.ssid);
			strncpy(m_config.password, password, sizeof m_config.password);
			strncpy(m_config.hostIp, hostIp, sizeof m_config.hostIp);
			m_config.useEmulator = useEmulator;
			m_config.numPixels = numPixels;
			m_config.hostPort = hostPort;


			EEPROM.begin(200);
			for(int i = 0; i < 200; ++i){
				EEPROM.write(i, 0);	
			}
			EEPROM.commit();
			EEPROM.end();
			EEPROM.begin(200);
			EEPROM.put(CONFIG_BEGIN, m_config);
			delay(200);
			EEPROM.commit();
			EEPROM.end();
		}
		config_t m_config;
	};



