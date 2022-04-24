
String get_help(){
  String help = "";
  help += "ping => Print I'm here :)\n";
  help += "help => Print all commands\n";
  return help;
}

String terminal_run(String input_line){
  String result = "Unknown command!";
  if(input_line == "ping"){
    result = "I'm here :)";
  }else if(input_line == "help"){
    result = get_help();
  }
  return result + "\n\n";
}
