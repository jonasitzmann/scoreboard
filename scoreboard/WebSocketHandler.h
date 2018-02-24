#include <ESP8266WiFi.h>
#include <WebSocketClient.h>
class WebSocketHandler{
  char* ssid = "hotspot";
  char* password = "fahrrad!";
  bool useHomeWifi = true;

  char* host = "192.168.43.206";
  int serverPort = 8000;
  WebSocketClient webSocketClient;

  WiFiClient client;
  public:
  WebSocketHandler(){
    if(useHomeWifi){
      ssid = "EasyBox-522111";
      password = "DdPA7As6kYKLDMKV";
      host = "192.168.2.112";
    }
  }
  void connectToServer(){
    connectToWifi();
    openWebSocket();
    handshake();
  }
  
  void connectToWifi(){
    WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
  }
  
  void openWebSocket(){
  if (client.connect(host, serverPort)) {
  } else {
    Serial.println("Connection failed.");
    while (1) {
      // Hang on failure
    }
  }
  }
  
  void handshake(){
    Serial.println("Handshaking");
    webSocketClient.path = "/";
    webSocketClient.host = host;
    if (webSocketClient.handshake(client)) {
    } else {
      Serial.println("Handshake failed.");
      while (1) {
        // Hang on failure
      }
    }
  }
  bool isConnected(){
    return client.connected();
  }
  String getData(){
    String data;
    webSocketClient.getData(data);
    return data;
  }
};

