
void update_io(){
  digitalWrite(RELAY1_PIN, board_io.output1);
  digitalWrite(RELAY2_PIN, board_io.output2);
  digitalWrite(RELAY3_PIN, board_io.output3);
  digitalWrite(RELAY4_PIN, board_io.output4);
  digitalWrite(RELAY5_PIN, board_io.output5);
  board_io.input1 = !digitalRead(INPUT1_PIN);
  board_io.input2 = !digitalRead(INPUT2_PIN);
  board_io.input3 = !digitalRead(INPUT3_PIN);
}


//================ Lamp Agent ================
#define LAMP_ON_TIME  600000    //10 minutes
void lampAgentLoop(){
  if((millis() - lastPressedButtonTime) <= LAMP_ON_TIME){
    board_io.output5 = true;
  }else{
    board_io.output5 = false;
  }
}
//---------------- Lamp Agent ----------------

void ioc_task(void * parameter){
  pinMode(BUZZER_PIN, OUTPUT); digitalWrite(BUZZER_PIN, LOW);
  pinMode(RELAY1_PIN, OUTPUT); digitalWrite(RELAY1_PIN, LOW);
  pinMode(RELAY2_PIN, OUTPUT); digitalWrite(RELAY2_PIN, LOW);
  pinMode(RELAY3_PIN, OUTPUT); digitalWrite(RELAY3_PIN, LOW);
  pinMode(RELAY4_PIN, OUTPUT); digitalWrite(RELAY4_PIN, LOW);
  pinMode(RELAY5_PIN, OUTPUT); digitalWrite(RELAY5_PIN, LOW);
  pinMode(VOLTAGE_PIN, INPUT);
  pinMode(INPUT1_PIN, INPUT_PULLUP);
  pinMode(INPUT2_PIN, INPUT_PULLUP);
  pinMode(INPUT3_PIN, INPUT_PULLUP);

  for (;;) {
    lampAgentLoop();
    update_io();
    
    vTaskDelay(pdMS_TO_TICKS(4));
  }
}