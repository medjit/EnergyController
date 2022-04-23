#define RXD2 16
#define TXD2 17

void victron_task(void * parameter){
  Serial1.begin(19200, SERIAL_8N1, RXD2, TXD2);
  Serial1.setRxBufferSize(400);
  String tempStr = "";
  for (;;) {
    while (Serial1.available() > 0) {
        char byteFromSerial = Serial1.read();
        //Serial.print(byteFromSerial);
        if(byteFromSerial != '\n'){
          tempStr += byteFromSerial;
        }else{
          //TelnetStream.println(tempStr);
          //Serial.println(tempStr);
          float calculated_val;
          if(tempStr.charAt(0) == 'V' && tempStr.charAt(1) == 'P' && tempStr.charAt(2) == 'V'){ //Panel voltage
            String val = tempStr.substring(4);
            calculated_val = atoi(val.c_str()) / 1000.0;
            TelnetStream.println("VE loop: Calc voltage: " + (String)(calculated_val));
          }else if(tempStr.charAt(0) == 'V' && tempStr.charAt(1) != 'P'){ //calc voltage
            String val = tempStr.substring(2);
            calculated_val = atoi(val.c_str()) / 1000.0;
            TelnetStream.println("VE loop: Calc voltage: " + (String)(calculated_val));
          }else if(tempStr.charAt(0) == 'I'){ // calc current
            String val = tempStr.substring(2);
            calculated_val = atol(val.c_str()) / 1000.0;
            TelnetStream.println("VE loop: Calc current: " + (String)(calculated_val));
          }else if(tempStr.charAt(0) == 'P' && tempStr.charAt(1) == 'P' && tempStr.charAt(2) == 'V'){ // Power
            String val = tempStr.substring(4);
            calculated_val = atoi(val.c_str());
            TelnetStream.println("VE loop: Calc power: " + (String)(calculated_val));
          }else if(tempStr.charAt(0) == 'H' && tempStr.charAt(1) == '1' && tempStr.charAt(2) == '9'){ // Yield total
            String val = tempStr.substring(4);
            calculated_val = atol(val.c_str()) / 100.0;
            TelnetStream.println("VE loop: Calc yield_total: " + (String)(calculated_val));
          }else if(tempStr.charAt(0) == 'H' && tempStr.charAt(1) == '2' && tempStr.charAt(2) == '0'){ // Yield today
            String val = tempStr.substring(4);
            calculated_val = atol(val.c_str()) / 100.0;
            TelnetStream.println("VE loop: Calc yield_today: " + (String)(calculated_val));
          }else if(tempStr.charAt(0) == 'H' && tempStr.charAt(1) == '2' && tempStr.charAt(2) == '1'){ // Maximum power today
            String val = tempStr.substring(4);
            calculated_val = atol(val.c_str());
            TelnetStream.println("VE loop: Calc max_power_today: " + (String)(calculated_val));
          }else if(tempStr.charAt(0) == 'H' && tempStr.charAt(1) == '2' && tempStr.charAt(2) == '2'){ // Yield yesterday
            String val = tempStr.substring(4);
            calculated_val = atol(val.c_str()) / 100.0;
            TelnetStream.println("VE loop: Calc yield_yesterday: " + (String)(calculated_val));
          }else if(tempStr.charAt(0) == 'H' && tempStr.charAt(1) == '2' && tempStr.charAt(2) == '3'){ // Maximum power Yesterday
            String val = tempStr.substring(4);
            calculated_val = atol(val.c_str());
            TelnetStream.println("VE loop: Calc max_power_yesterday: " + (String)(calculated_val));
          }else if(tempStr.charAt(0) == 'C' && tempStr.charAt(1) == 'S'){ // Charger State
            String val = tempStr.substring(3);
            calculated_val = atol(val.c_str());
            TelnetStream.println("VE loop: Calc charger_state: " + (String)(calculated_val));
          }
          tempStr = "";
        }
    }
    vTaskDelay(pdMS_TO_TICKS(950));
  }
}
