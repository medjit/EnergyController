unsigned long lastPressedButtonTime = 0;

struct usage_flags_t{
  boolean blynk = false;
};


struct data_field_t{
  float value;
  usage_flags_t flags;
  unsigned long  update_timestamp = 0;
};


struct victron_data_t{
  data_field_t panel_voltage;
  data_field_t battery_voltage;
  data_field_t battery_current;
  data_field_t power;
  data_field_t yield_total;
  data_field_t yield_today;
  data_field_t max_pwr_today;
  data_field_t yield_yesterday;
  data_field_t max_pwr_yesterday;
  data_field_t charger_state;
  boolean enable_charger = true;
}ve_data;

struct daly_bms_data_t{
  data_field_t packVoltage;
  data_field_t packCurrent;
  data_field_t packSOC;
  data_field_t tempAverage;
  data_field_t maxCellVNum;
  data_field_t maxCellV;
  data_field_t minCellVNum;
  data_field_t minCellV;
  data_field_t bmsCycles;
  data_field_t bmsHeartBeat;
  data_field_t disChargeFetState;
  data_field_t chargeFetState;
  data_field_t resCapacityAh;
  data_field_t cell1V;
  data_field_t cell2V;
  data_field_t cell3V;
  data_field_t cell4V;
  data_field_t cell5V;
  data_field_t cell6V;
  data_field_t cell7V;
  data_field_t cell8V;
  data_field_t levelOneCellVoltageTooHigh;
}daly_data;

struct board_io_t{
  boolean input1 = false;
  boolean input2 = false;
  boolean input3 = false;
  boolean output1 = false;
  boolean output2 = false;
  boolean output3 = false;
  boolean output4 = true;
  boolean output5 = false;
}board_io;
