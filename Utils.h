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

void doBeep(byte type){
  switch(type){
    case 0:
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(pdMS_TO_TICKS(30));
      digitalWrite(BUZZER_PIN, LOW);
      break;
    case 1:
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(pdMS_TO_TICKS(100));
      digitalWrite(BUZZER_PIN, LOW);
      break;
    case 2:
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(pdMS_TO_TICKS(30));
      digitalWrite(BUZZER_PIN, LOW);
      vTaskDelay(pdMS_TO_TICKS(100));
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(pdMS_TO_TICKS(30));
      digitalWrite(BUZZER_PIN, LOW);
      break;
    case 3:
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(pdMS_TO_TICKS(1500));
      digitalWrite(BUZZER_PIN, LOW);
      break;
    default:
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(pdMS_TO_TICKS(1000));
      digitalWrite(BUZZER_PIN, LOW);
  }
}

float mapFloat(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
  return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow; 
}

#define SAMPLES   1000
#define HIGH_RES  9930.0
#define LOW_RES   996.0
float getBoardVoltage(){
  float voltage = 0.0;
  unsigned long rawData = 0;
  for(unsigned int i = 0; i <= SAMPLES; i ++){
    rawData += analogRead(VOLTAGE_PIN);
  }
  rawData = rawData / SAMPLES;
  float rawVoltage = (rawData * 3.3) / 4096.0;
  voltage = rawVoltage / (LOW_RES / (HIGH_RES + LOW_RES));
    voltage = mapFloat(voltage, 10.55, 25.8, 11.95, 27.29);
  return voltage;
}

boolean switch_boiler(){
  if(ve_data.enable_charger == false){
    return true;
  }else if(ve_data.power.value > 300){
    return true;
  }else if(board_data.voltage.value > 27.00){
    return true;
  }else if(ve_data.charger_state.value == 5){
    return true;
  }else if(ve_data.yield_today.value > 6.00){
    return true;
  }else{
    return false;
  }
}
