
#include "Credentials.h"
#include "OTA.h"
#include "VictronReceiver.h"

void setup(){
  xTaskCreate(ota_task,     "OTA_HANDLE", 10000, NULL, 1, NULL);
  xTaskCreate(victron_task, "VE_HANDLE",  10000, NULL, 1, NULL);
}

void loop(){
  vTaskDelay(pdMS_TO_TICKS(3500));
}
