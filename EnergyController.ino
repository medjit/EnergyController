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

#include <DS3231.h>
#include <Wire.h>
#include "Adafruit_AHT10.h"
#include "Credentials.h"
#include "DataStructures.h"
#include "EepromUtils.h"
#include "Terminal.h"
#include "Utils.h"
#include "IOControl.h"
#include "OTA.h"
#include "Blynk.h"
#include "MQTT.h"
#include "VictronReceiver.h"

DS3231 Clock;
Adafruit_AHT10 ahtBattery;
Adafruit_AHT10 ahtAmbient;

void setup(){
  eeprom_init();
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

  ahtBattery.begin(&Wire, 0, 0x38);
  ahtAmbient.begin(&Wire, 0, 0x39);
}

void loop(){

  board_data.voltage.value = getBoardVoltage();
  board_data.voltage.update_timestamp = millis();
  board_data.voltage.flags.blynk = true;
  board_data.voltage.flags.mqtt = true;
  
  board_data.wifi_rssi.value = WiFi.RSSI();
  board_data.wifi_rssi.update_timestamp = millis();
  board_data.wifi_rssi.flags.blynk = true;
  board_data.wifi_rssi.flags.mqtt = true;
  
  board_data.rtc_temp.value = Clock.getTemperature();
  board_data.rtc_temp.update_timestamp = millis();
  board_data.rtc_temp.flags.blynk = true;
  board_data.rtc_temp.flags.mqtt = true;
  
  sensors_event_t humidityBat, tempBat;
  ahtBattery.getEvent(&humidityBat, &tempBat);
  board_data.battery_temp.value = tempBat.temperature;
  board_data.battery_temp.update_timestamp = millis();
  board_data.battery_temp.flags.blynk = true;
  board_data.battery_temp.flags.mqtt = true;
  
  board_data.battery_humidity.value = humidityBat.relative_humidity;
  board_data.battery_humidity.update_timestamp = millis();
  board_data.battery_humidity.flags.blynk = true;
  board_data.battery_humidity.flags.mqtt = true;
  
  sensors_event_t humidityAmbient, tempAmbient;
  ahtAmbient.getEvent(&humidityAmbient, &tempAmbient);
  board_data.ambient_temp.value = tempAmbient.temperature;
  board_data.ambient_temp.update_timestamp = millis();
  board_data.ambient_temp.flags.blynk = true;
  board_data.ambient_temp.flags.mqtt = true;
  
  board_data.ambient_humidity.value = humidityAmbient.relative_humidity;
  board_data.ambient_humidity.update_timestamp = millis();
  board_data.ambient_humidity.flags.blynk = true;
  board_data.ambient_humidity.flags.mqtt = true;
  
  vTaskDelay(pdMS_TO_TICKS(20000));
}
