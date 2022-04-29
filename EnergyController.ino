#define VOLTAGE_PIN   36
#define BUZZER_PIN    5
#define RELAY1_PIN    26
#define RELAY2_PIN    27
#define RELAY3_PIN    14
#define RELAY4_PIN    12
#define RELAY5_PIN    13
#define LAMP_OUTPUT   5
#define STATUS_LED_PIN 15
#define INPUT1_PIN    32
#define INPUT2_PIN    33
#define INPUT3_PIN    25



#include "Credentials.h"
#include "DataStructures.h"
#include "Terminal.h"
#include "Utils.h"
#include "IOControl.h"
#include "OTA.h"
#include "Blynk.h"
#include "MQTT.h"
#include "VictronReceiver.h"


void setup(){
  delay(10);
  xTaskCreate(ioc_task,     "IOC_HANDLE",    10000, NULL,       1, NULL);
  delay(10);
  xTaskCreate(victron_task, "VE_HANDLE",     10000, &ve_data,   1, NULL);
  delay(10);
  xTaskCreate(ota_task,     "OTA_HANDLE",    10000, NULL,       1, NULL);
  delay(10);
  xTaskCreate(blynk_task,   "BLYNK_HANDLE",  10000, NULL,       1, NULL);
  delay(10);
  xTaskCreate(mqtt_task,    "MQTT_HANDLE",   10000, NULL,       1, NULL);
  //doBeep(2);
}

void loop(){
  vTaskDelay(pdMS_TO_TICKS(3500));
}
