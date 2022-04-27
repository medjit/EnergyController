#include <HardwareSerial.h>
#include "daly-bms-uart.h"

//Do not forget to change Serial1 pins in 
//AppData>Local>arduino>packages>esp32>2.0.2>cores>esp32>harwareSerail.cpp

HardwareSerial DalyPort(1);

Daly_BMS_UART bms(DalyPort);

void daly_task(void * parameter){

  bms.Init();
  
  for (;;) {
    vTaskDelay(pdMS_TO_TICKS(2000));
    // call to update the data from the bms
    //if(bms.update()){
  bms.update();
      // And print them out!
      TelnetStream.println("basic BMS Data:              " + (String)bms.get.packVoltage + "V " + (String)bms.get.packCurrent + "I " + (String)bms.get.packSOC + "\% ");
      TelnetStream.println("Package Temperature:         " + (String)bms.get.tempAverage);
      TelnetStream.println("Highest Cell Voltage Nr:     " + (String)bms.get.maxCellVNum + " with voltage " + (String)(bms.get.maxCellmV / 1000));
      TelnetStream.println("Lowest Cell Voltage Nr:      " + (String)bms.get.minCellVNum + " with voltage " + (String)(bms.get.minCellmV / 1000));
      TelnetStream.println("Number of Cells:             " + (String)bms.get.numberOfCells);
      TelnetStream.println("Number of Temp Sensors:      " + (String)bms.get.numOfTempSensors);
      TelnetStream.println("BMS Chrg / Dischrg Cycles:   " + (String)bms.get.bmsCycles);
      TelnetStream.println("BMS Heartbeat:               " + (String)bms.get.bmsHeartBeat); // cycle 0-255
      TelnetStream.println("Discharge MOSFet Status:     " + (String)bms.get.disChargeFetState);
      TelnetStream.println("Charge MOSFet Status:        " + (String)bms.get.chargeFetState);
      TelnetStream.println("Remaining Capacity mAh:      " + (String)bms.get.resCapacitymAh);
      //... any many many more data
    
      for (size_t i = 0; i < size_t(bms.get.numberOfCells); i++)
      {
        TelnetStream.println("Remaining Capacity mV:      " + (String)bms.get.cellVmV[i]);
      }
    
      // for alarm flags - for all flags see the alarm struct in daly-bms-uart.h and refer to the datasheet
      TelnetStream.println("Level one Cell V to High:    " + (String)bms.alarm.levelOneCellVoltageTooHigh);
    
      /**
       * Advanced functions:
       * bms.setBmsReset(); //Reseting the BMS, after reboot the MOS Gates are enabled!
       * bms.setDischargeMOS(true); Switches on the discharge Gate
       * bms.setDischargeMOS(false); Switches off thedischarge Gate
       * bms.setChargeMOS(true); Switches on the charge Gate
       * bms.setChargeMOS(false); Switches off the charge Gate
       */
    //}
  }
}
