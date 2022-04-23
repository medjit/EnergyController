// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID ENERGY_CONTROLLER_BLYNK_TEMPLATE_ID
#define BLYNK_DEVICE_NAME ENERGY_CONTROLLER_BLYNK_DEVICE_NAME
#define BLYNK_AUTH_TOKEN ENERGY_CONTROLLER_BLYNK_AUTH_TOKEN


// Comment this out to disable prints and save space
//#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

char *uptime(unsigned long milli){
  static char _return[32];
  unsigned long secs=milli/1000, mins=secs/60;
  unsigned int hours=mins/60, days=hours/24;
  milli-=secs*1000;
  secs-=mins*60;
  mins-=hours*60;
  hours-=days*24;
  sprintf(_return,"Uptime: %d days %2.2d:%2.2d:%2.2d.%3.3d", (byte)days, (byte)hours, (byte)mins, (byte)secs, (int)milli);
  return _return;
}

char *uptime(){
  return (char *)uptime(millis()); // call original uptime function with unsigned long millis() value
}

void blynk_task(void * parameter){
  Blynk.begin(auth, MY_SSID, MY_PASS);
  for (;;) {
    Blynk.virtualWrite(V0, uptime());
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}
