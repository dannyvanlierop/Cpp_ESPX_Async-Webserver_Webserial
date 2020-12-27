// Replace with your network credentials
#define WIFI_SSID        "SSID"
#define WIFI_PASSWORD    "PASSWORD"

#include <Arduino.h>
// Import required libraries
#if defined ARDUINO_ARCH_ESP32 || ESP32 || ARDUINO_ESP32_DEV
  #include <WiFi.h>
  #include <AsyncTCP.h>
#elif defined ARDUINO_ARCH_ESP8266 || ESP8266 || ARDUINO_ESP8266_WEMOS_D1MINI
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

AsyncWebServer server(80);

void recvMsg(uint8_t *data, size_t len){
  WebSerial.println("Received Data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
  }
  WebSerial.println(d);
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    // WebSerial is accessible at "<IP Address>/webserial" in browser
    WebSerial.begin(&server);
    WebSerial.msgCallback(recvMsg);
    server.begin();
}


long secondLast = millis()/1000;
void loop() {
  int secondNow = millis()/1000;
  if(secondLast != secondNow)
  {
    secondLast = secondNow;
    WebSerial.print("\n secondNow: " + String(secondNow) );
  }  
}
