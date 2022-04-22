
#include "Credentials.h"
#include "OTA.h"

void setup(){
  xTaskCreate(ota_task, "OTA_HANDLE", 10000, NULL, 1, NULL);
}

void loop(){
  
}
