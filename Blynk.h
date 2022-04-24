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

BLYNK_WRITE(V41){
  doBeep(0);
  if(param.asInt() == 1) board_io.output1 = true;
  else                   board_io.output1 = false;
}
BLYNK_WRITE(V42){
  doBeep(0);
  if(param.asInt() == 1) board_io.output2 = true;
  else                   board_io.output2 = false;
}
BLYNK_WRITE(V43){
  doBeep(0);
  if(param.asInt() == 1) board_io.output3 = true;
  else                   board_io.output3 = false;
}
BLYNK_WRITE(V44){
  doBeep(0);
  if(param.asInt() == 1) board_io.output4 = true;
  else                   board_io.output4 = false;
}
BLYNK_WRITE(V45){ //Lamp Output
  doBeep(0);
  if(param.asInt() == 1) lastPressedButtonTime = millis();
  else                   lastPressedButtonTime = 0;
}
BLYNK_WRITE(V14){ //remote control solar charger
  doBeep(0);
  if(param.asInt() == 1) ve_data.enable_charger = true;
  else                   ve_data.enable_charger = false;
}

BLYNK_WRITE(V100){ //Blynk Terminal interface
  Blynk.virtualWrite(V100, terminal_run(param.asStr()));
}

void ve_data_update(){
  if(ve_data.panel_voltage.flags.blynk){
    Blynk.virtualWrite(V4, ve_data.panel_voltage.value);
    ve_data.panel_voltage.flags.blynk = false;
  }

  if(ve_data.battery_voltage.flags.blynk){
    Blynk.virtualWrite(V2, ve_data.battery_voltage.value);
    ve_data.battery_voltage.flags.blynk = false;
  }

  if(ve_data.battery_current.flags.blynk){
    Blynk.virtualWrite(V3, ve_data.battery_current.value);
    ve_data.battery_current.flags.blynk = false;
  }

  if(ve_data.power.flags.blynk){
    Blynk.virtualWrite(V1, ve_data.power.value);
    ve_data.power.flags.blynk = false;
  }

  if(ve_data.yield_total.flags.blynk){
    Blynk.virtualWrite(V8, ve_data.yield_total.value);
    ve_data.yield_total.flags.blynk = false;
  }

  if(ve_data.yield_today.flags.blynk){
    Blynk.virtualWrite(V9, ve_data.yield_today.value);
    ve_data.yield_today.flags.blynk = false;
  }

  if(ve_data.max_pwr_today.flags.blynk){
    Blynk.virtualWrite(V10, ve_data.max_pwr_today.value);
    ve_data.max_pwr_today.flags.blynk = false;
  }

  if(ve_data.yield_yesterday.flags.blynk){
    Blynk.virtualWrite(V11, ve_data.yield_yesterday.value);
    ve_data.yield_yesterday.flags.blynk = false;
  }

  if(ve_data.max_pwr_yesterday.flags.blynk){
    Blynk.virtualWrite(V12, ve_data.max_pwr_yesterday.value);
    ve_data.max_pwr_yesterday.flags.blynk = false;
  }

  if(ve_data.charger_state.flags.blynk){
    String ve_operation_state = "Unknown";
    switch((int)ve_data.charger_state.value){
            case 0: ve_operation_state = "Off";        break;
            case 2: ve_operation_state = "Fault";      break;
            case 3: ve_operation_state = "Bulk";       break;
            case 4: ve_operation_state = "Absorption"; break;
            case 5: ve_operation_state = "Float";      break;
    }
    Blynk.virtualWrite(V5, ve_operation_state);
    ve_data.charger_state.flags.blynk = false;
  }
}


void blynk_task(void * parameter){
  Blynk.begin(auth, MY_SSID, MY_PASS);
  
  for (;;) {
    Blynk.run();
    Blynk.virtualWrite(V0, uptime());
    Blynk.virtualWrite(V41, board_io.output1);
    Blynk.virtualWrite(V42, board_io.output2);
    Blynk.virtualWrite(V43, board_io.output3);
    Blynk.virtualWrite(V44, board_io.output4);
    Blynk.virtualWrite(V45, board_io.output5);
    Blynk.virtualWrite(V51, board_io.input1);
    Blynk.virtualWrite(V52, board_io.input2);
    Blynk.virtualWrite(V53, board_io.input3);
    ve_data_update();

    Blynk.virtualWrite(V14, ve_data.enable_charger);
        
    Blynk.run();
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}
