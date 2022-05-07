
String get_help(){
  String help = "";
  help += "ping => Print I'm here :)\n";
  help += "help => Print all commands\n";
  help += "ESP.RESTART => restart esp after 5 seconds\n";
  help += "setDefState => set current to default state\n";
  help += "autoBoilerOn => set auto boiler to on\n";
  help += "autoBoilerOff => set auto boiler to off\n";
  help += "getAutoBoiler => return auto boiler state\n";
  return help;
}

void rst_esp(void * parameter){
  vTaskDelay(pdMS_TO_TICKS(5000));
  ESP.restart();
}

String terminal_run(String input_line){
  String result = "Unknown command!";
  String command, param1, param2;
  if(input_line.indexOf(" ") > 0){
    command = input_line.substring(0, input_line.indexOf(" "));
    String rest_of_line = input_line.substring(input_line.indexOf(" "), input_line.length() - 1);
  }else{
    command = input_line;
  }
  
  if(command == "ping"){
    result = "I'm here :)";
  }else if(command == "help"){
    result = get_help();
  }else if(command == "ESP.RESTART"){
    result = "Restarting the ESP in 5 sec.";
    xTaskCreate(rst_esp, "RST_HANDLE", 1000, NULL,1, NULL);
  }else if(command == "setDefState"){
    result = "Setting current state to default.";
    set_default_state();
  }else if(command == "autoBoilerOn"){
    result = "Setting ON auto boiler.";
    board_data.auto_boiler = true;
    update_to_eeprom(AUTO_BOILER_STATE_EEPROM_ADDRESS, board_data.auto_boiler);
    EEPROM.commit();
  }else if(command == "autoBoilerOff"){
    result = "Setting FF auto boiler.";
    board_data.auto_boiler = false;
    update_to_eeprom(AUTO_BOILER_STATE_EEPROM_ADDRESS, board_data.auto_boiler);
    EEPROM.commit();
  }else if(command == "getAutoBoiler"){
    if(board_data.auto_boiler){
      result = "Auto boiler is on!";
    }else{
      result = "Auto boiler is off!";
    }
  }
  return result + "\n\n";
}
