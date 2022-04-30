
String get_help(){
  String help = "";
  help += "ping => Print I'm here :)\n";
  help += "help => Print all commands\n";
  help += "ESP.RESTART => restart esp after 5 seconds\n";
  return help;
}

void rst_esp(void * parameter){
  vTaskDelay(pdMS_TO_TICKS(5000));
  ESP.restart();
}

String terminal_run(String input_line){
  String result = "Unknown command!";
  if(input_line == "ping"){
    result = "I'm here :)";
  }else if(input_line == "help"){
    result = get_help();
  }else if(input_line == "ESP.RESTART"){
    result = "Restarting the ESP in 5 sec.";
    xTaskCreate(rst_esp, "RST_HANDLE", 1000, NULL,1, NULL);
  }
  return result + "\n\n";
}
