
#include "Credentials.h"
#include "DataStructures.h"
#include "OTA.h"
#include "VictronReceiver.h"

victron_data_t ve_data;

void setup(){
  xTaskCreate(ota_task,     "OTA_HANDLE", 10000, NULL, 1, NULL);
  xTaskCreate(victron_task, "VE_HANDLE",  10000, &ve_data, 1, NULL);
}

void loop(){
  vTaskDelay(pdMS_TO_TICKS(3500));
}
