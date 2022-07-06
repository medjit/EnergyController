#include <EEPROM.h>

#define EEPROM_SIZE 255

#define OUT1_DEFAULT_STATE_EEPROM_ADDRESS 1
#define OUT2_DEFAULT_STATE_EEPROM_ADDRESS 2
#define OUT3_DEFAULT_STATE_EEPROM_ADDRESS 3
#define OUT4_DEFAULT_STATE_EEPROM_ADDRESS 4
#define OUT5_DEFAULT_STATE_EEPROM_ADDRESS 5
#define VE_CHARGER_DEFAULT_STATE_EEPROM_ADDRESS 6
#define AUTO_BOILER_STATE_EEPROM_ADDRESS 7


void update_to_eeprom(byte address, byte value){
  if(value != EEPROM.read(address)){
    EEPROM.write(address, value);
  }
}

void set_default_state(){
  update_to_eeprom(OUT1_DEFAULT_STATE_EEPROM_ADDRESS, board_data.output1);
  update_to_eeprom(OUT2_DEFAULT_STATE_EEPROM_ADDRESS, board_data.output2);
  update_to_eeprom(OUT3_DEFAULT_STATE_EEPROM_ADDRESS, board_data.output3);
  update_to_eeprom(OUT4_DEFAULT_STATE_EEPROM_ADDRESS, board_data.output4);
  update_to_eeprom(OUT5_DEFAULT_STATE_EEPROM_ADDRESS, board_data.output5);
  update_to_eeprom(VE_CHARGER_DEFAULT_STATE_EEPROM_ADDRESS, ve_data.enable_charger);
  EEPROM.commit();
}

void eeprom_init(){
  EEPROM.begin(EEPROM_SIZE);

  board_data.output1 = EEPROM.read(OUT1_DEFAULT_STATE_EEPROM_ADDRESS);
  board_data.output2 = EEPROM.read(OUT2_DEFAULT_STATE_EEPROM_ADDRESS);
  board_data.output3 = EEPROM.read(OUT3_DEFAULT_STATE_EEPROM_ADDRESS);
  board_data.output4 = EEPROM.read(OUT4_DEFAULT_STATE_EEPROM_ADDRESS);
  board_data.output5 = EEPROM.read(OUT5_DEFAULT_STATE_EEPROM_ADDRESS);
  board_data.auto_boiler = EEPROM.read(AUTO_BOILER_STATE_EEPROM_ADDRESS);

  ve_data.enable_charger = EEPROM.read(VE_CHARGER_DEFAULT_STATE_EEPROM_ADDRESS);
}
