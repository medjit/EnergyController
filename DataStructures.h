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
