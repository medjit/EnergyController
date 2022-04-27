#include "daly-bms-uart.h"

//Do not forget to change Serial1 pins in 
//AppData>Local>arduino>packages>esp32>2.0.2>cores>esp32>harwareSerail.cpp

Daly_BMS_UART bms(Serial1);

void set_daly_value(data_field_t *field_ptr, float new_val, String field_name){
  data_field_t *field = (data_field_t*)field_ptr;
  field->value = new_val;
  field->update_timestamp = millis();
  field->flags.blynk = true;
  TelnetStream.println("DALY_RECEIVER: " + field_name + ": " + (String)new_val);
}

void daly_task(void * parameter){
  daly_bms_data_t *daly_data = (daly_bms_data_t*)parameter;
  bms.Init();
  
  for (;;) {
    vTaskDelay(pdMS_TO_TICKS(2000));
    // call to update the data from the bms
    if(bms.update()){
      // And print them out!
      //TelnetStream.println("basic BMS Data:              " + (String)bms.get.packVoltage + "V " + (String)bms.get.packCurrent + "I " + (String)bms.get.packSOC + "\% ");
      set_daly_value(&daly_data->packVoltage, bms.get.packVoltage, "packVoltage");
      set_daly_value(&daly_data->packCurrent, bms.get.packCurrent, "packCurrent");
      set_daly_value(&daly_data->packSOC, bms.get.packSOC, "packSOC");
      
      //TelnetStream.println("Package Temperature:         " + (String)bms.get.tempAverage);
      set_daly_value(&daly_data->tempAverage, bms.get.tempAverage, "tempAverage");
      
      //TelnetStream.println("Highest Cell Voltage Nr:     " + (String)bms.get.maxCellVNum + " with voltage " + (String)(bms.get.maxCellmV / 1000));
      set_daly_value(&daly_data->maxCellVNum, bms.get.maxCellVNum, "maxCellVNum");
      set_daly_value(&daly_data->maxCellV, bms.get.maxCellmV / 1000.0, "maxCellV");
      
      //TelnetStream.println("Lowest Cell Voltage Nr:      " + (String)bms.get.minCellVNum + " with voltage " + (String)(bms.get.minCellmV / 1000));
      set_daly_value(&daly_data->minCellVNum, bms.get.minCellVNum, "minCellVNum");
      set_daly_value(&daly_data->minCellV, bms.get.minCellmV / 1000.0, "minCellV");
      
      //TelnetStream.println("BMS Chrg / Dischrg Cycles:   " + (String)bms.get.bmsCycles);
      set_daly_value(&daly_data->bmsCycles, bms.get.bmsCycles, "bmsCycles");
      
      //TelnetStream.println("BMS Heartbeat:               " + (String)bms.get.bmsHeartBeat); // cycle 0-255
      set_daly_value(&daly_data->bmsHeartBeat, bms.get.bmsHeartBeat, "bmsHeartBeat");
      
      //TelnetStream.println("Discharge MOSFet Status:     " + (String)bms.get.disChargeFetState);
      set_daly_value(&daly_data->disChargeFetState, bms.get.disChargeFetState, "disChargeFetState");
      
      //TelnetStream.println("Charge MOSFet Status:        " + (String)bms.get.chargeFetState);
      set_daly_value(&daly_data->chargeFetState, bms.get.chargeFetState, "chargeFetState");
      
      //TelnetStream.println("Remaining Capacity mAh:      " + (String)bms.get.resCapacitymAh);
      set_daly_value(&daly_data->resCapacityAh, bms.get.resCapacitymAh / 1000.0, "resCapacityAh");
      //... any many many more data
    
      //for (size_t i = 0; i < size_t(bms.get.numberOfCells); i++){
      //  TelnetStream.println("Remaining Capacity mV:      " + (String)bms.get.cellVmV[i]);
      //}
      set_daly_value(&daly_data->cell1V, bms.get.cellVmV[0] / 1000.0, "cell1V");
      set_daly_value(&daly_data->cell2V, bms.get.cellVmV[1] / 1000.0, "cell2V");
      set_daly_value(&daly_data->cell3V, bms.get.cellVmV[2] / 1000.0, "cell3V");
      set_daly_value(&daly_data->cell4V, bms.get.cellVmV[3] / 1000.0, "cell4V");
      set_daly_value(&daly_data->cell5V, bms.get.cellVmV[4] / 1000.0, "cell5V");
      set_daly_value(&daly_data->cell6V, bms.get.cellVmV[5] / 1000.0, "cell6V");
      set_daly_value(&daly_data->cell7V, bms.get.cellVmV[6] / 1000.0, "cell7V");
      set_daly_value(&daly_data->cell8V, bms.get.cellVmV[7] / 1000.0, "cell8V");
    
      // for alarm flags - for all flags see the alarm struct in daly-bms-uart.h and refer to the datasheet
      //TelnetStream.println("Level one Cell V to High:    " + (String)bms.alarm.levelOneCellVoltageTooHigh);
      set_daly_value(&daly_data->levelOneCellVoltageTooHigh, bms.alarm.levelOneCellVoltageTooHigh, "levelOneCellVoltageTooHigh");
      /**
       * Advanced functions:
       * bms.setBmsReset(); //Reseting the BMS, after reboot the MOS Gates are enabled!
       * bms.setDischargeMOS(true); Switches on the discharge Gate
       * bms.setDischargeMOS(false); Switches off thedischarge Gate
       * bms.setChargeMOS(true); Switches on the charge Gate
       * bms.setChargeMOS(false); Switches off the charge Gate
       */
    }
  }
}
