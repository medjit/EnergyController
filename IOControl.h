
void update_io(){
  digitalWrite(RELAY1_PIN, board_data.output1);
  digitalWrite(RELAY2_PIN, board_data.output2);
  digitalWrite(RELAY3_PIN, board_data.output3);
  digitalWrite(RELAY4_PIN, board_data.output4);
  digitalWrite(RELAY5_PIN, board_data.output5);
  board_data.input1 = !digitalRead(INPUT1_PIN);
  board_data.input2 = !digitalRead(INPUT2_PIN);
  board_data.input3 = !digitalRead(INPUT3_PIN);
}


//================ Lamp Agent ================
#define LAMP_ON_TIME  600000    //10 minutes
void lampAgentLoop(){
  if((millis() - lastPressedButtonTime) <= LAMP_ON_TIME){
    board_data.output5 = true;
  }else{
    board_data.output5 = false;
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
  pinMode(UP_BTN_PIN, INPUT);
  pinMode(DOWN_BTN_PIN, INPUT);
  pinMode(OK_BTN_PIN, INPUT);

  for (;;) {
    lampAgentLoop();
    update_io();
    if(digitalRead(UP_BTN_PIN) == LOW || digitalRead(DOWN_BTN_PIN) == LOW || digitalRead(OK_BTN_PIN) == LOW){
      lastPressedButtonTime = millis();
      doBeep(0);
    }
    vTaskDelay(pdMS_TO_TICKS(4));
  }
}
