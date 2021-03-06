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

unsigned int get_boiler_power(float voltage){
  if(board_data.output4 == 0) return 0;
  float amps = voltage / 18.0;
  return (amps * voltage);
}

BLYNK_WRITE(V41){
  doBeep(0);
  if(param.asInt() == 1) board_data.output1 = true;
  else                   board_data.output1 = false;
}
BLYNK_WRITE(V42){
  doBeep(0);
  if(param.asInt() == 1) board_data.output2 = true;
  else                   board_data.output2 = false;
}
BLYNK_WRITE(V43){
  doBeep(0);
  if(param.asInt() == 1) board_data.output3 = true;
  else                   board_data.output3 = false;
}
BLYNK_WRITE(V44){
  doBeep(0);
  if(param.asInt() == 1) board_data.output4 = true;
  else                   board_data.output4 = false;
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

void board_data_update(){
  Blynk.virtualWrite(V41, board_data.output1);
  Blynk.virtualWrite(V68, !board_data.output1);
  Blynk.virtualWrite(V42, board_data.output2);
  Blynk.virtualWrite(V43, board_data.output3);
  Blynk.virtualWrite(V44, board_data.output4);
  Blynk.virtualWrite(V45, board_data.output5);
  Blynk.virtualWrite(V51, board_data.input1);
  Blynk.virtualWrite(V52, board_data.input2);
  Blynk.virtualWrite(V53, board_data.input3);
    
  if(board_data.voltage.flags.blynk){
    Blynk.virtualWrite(V65, board_data.voltage.value);
    board_data.voltage.flags.blynk = false;
  }
  
  if(board_data.wifi_rssi.flags.blynk){
    Blynk.virtualWrite(V66, board_data.wifi_rssi.value);
    board_data.wifi_rssi.flags.blynk = false;
  }
  
  if(board_data.rtc_temp.flags.blynk){
    Blynk.virtualWrite(V60, board_data.rtc_temp.value);
    board_data.rtc_temp.flags.blynk = false;
  }
  
  if(board_data.battery_temp.flags.blynk){
    Blynk.virtualWrite(V63, board_data.battery_temp.value);
    board_data.battery_temp.flags.blynk = false;
  }
  
  if(board_data.battery_humidity.flags.blynk){
    Blynk.virtualWrite(V64, board_data.battery_humidity.value);
    board_data.battery_humidity.flags.blynk = false;
  }
  
  if(board_data.ambient_temp.flags.blynk){
    Blynk.virtualWrite(V61, board_data.ambient_temp.value);
    board_data.ambient_temp.flags.blynk = false;
  }
  
  if(board_data.ambient_humidity.flags.blynk){
    Blynk.virtualWrite(V62, board_data.ambient_humidity.value);
    board_data.ambient_humidity.flags.blynk = false;
  }
}

void blynk_task(void * parameter){
  Blynk.begin(auth, MY_SSID, MY_PASS);
  
  for (;;) {
    Blynk.run();
    Blynk.virtualWrite(V0, uptime());
    ve_data_update();
    board_data_update();
    
    Blynk.virtualWrite(V14, ve_data.enable_charger);
    Blynk.virtualWrite(V67, get_boiler_power(ve_data.panel_voltage.value));
        
    Blynk.run();
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}
