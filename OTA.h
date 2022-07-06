#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <TelnetStream.h>
#include "libs/AsyncTCP/src/AsyncTCP.h"
#include "libs/ESPAsyncWebServer/src/ESPAsyncWebServer.h"
#include "libs/AsyncElegantOTA/src/AsyncElegantOTA.h"
AsyncWebServer server(80);

const char* nameprefix = ENERGY_CONTROLLER_DEVICE_NAME;
const char* ssid = MY_SSID;
const char* password = MY_PASS;

#define WIFI_RECONNECT_INTERVAL 20000
unsigned long last_reconnection = 0;

void wifi_agent_loop(){
  if(WiFi.status() != WL_CONNECTED){
    if(millis() - last_reconnection >= WIFI_RECONNECT_INTERVAL){
      last_reconnection = millis();
      WiFi.disconnect();
      WiFi.reconnect();
    }
  }
}


void ota_task(void * parameter){
  // Configure and start the WiFi station
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.setHostname(nameprefix);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(pdMS_TO_TICKS(500));
  }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! This is a sample response. GoTo /update to upload new firmware.");
  });

  AsyncElegantOTA.begin(&server);    // Start AsyncElegantOTA
  server.begin();
  TelnetStream.begin();


  for (;;) {
    wifi_agent_loop();
    vTaskDelay(pdMS_TO_TICKS(3500));
  }
}
