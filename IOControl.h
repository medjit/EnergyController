// setting PWM properties
#define STATUS_LED_PWM_FREQ 1000
#define STATUS_LED_CHANEL 0
#define STATUS_LED_PWM_RESOLUTION  8


void update_io(){
  digitalWrite(RELAY1_PIN, board_data.output1);
  digitalWrite(RELAY2_PIN, board_data.output2);
  digitalWrite(RELAY3_PIN, board_data.output3);
  digitalWrite(RELAY4_PIN, board_data.output4);
  digitalWrite(RELAY5_PIN, board_data.output5);
  board_data.input1 = !digitalRead(INPUT1_PIN);
  board_data.input2 = !digitalRead(INPUT2_PIN);
  board_data.input3 = !digitalRead(INPUT3_PIN);
  ledcWrite(STATUS_LED_CHANEL, board_data.status_led_val);
}

//============= Status LED Agent =============
unsigned long last_blink_cycle = 0;
boolean breath_led_dirrection = true;
void statusLedLoop(){
  if(board_data.wifi_status == true){
    byte temp_val = board_data.status_led_val;
    if(breath_led_dirrection){
      if(temp_val == 255)breath_led_dirrection = false;
      else temp_val++;
    }else{
      if(temp_val == 0)breath_led_dirrection = false;
      else temp_val--;
    }
    board_data.status_led_val = temp_val;
  }else{ // led blink
    if(millis() - last_blink_cycle > 250){
      if(board_data.status_led_val > 0) board_data.status_led_val = 0;
      else                              board_data.status_led_val = 255;
    }
  }
}
//------------- Status LED Agent -------------

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
  pinMode(STATUS_LED_PIN, OUTPUT); digitalWrite(STATUS_LED_PIN, HIGH);
  pinMode(BUZZER_PIN, OUTPUT);     digitalWrite(BUZZER_PIN, LOW);
  pinMode(RELAY1_PIN, OUTPUT);     digitalWrite(RELAY1_PIN, LOW);
  pinMode(RELAY2_PIN, OUTPUT);     digitalWrite(RELAY2_PIN, LOW);
  pinMode(RELAY3_PIN, OUTPUT);     digitalWrite(RELAY3_PIN, LOW);
  pinMode(RELAY4_PIN, OUTPUT);     digitalWrite(RELAY4_PIN, LOW);
  pinMode(RELAY5_PIN, OUTPUT);     digitalWrite(RELAY5_PIN, LOW);
  pinMode(VOLTAGE_PIN, INPUT);
  pinMode(INPUT1_PIN, INPUT_PULLUP);
  pinMode(INPUT2_PIN, INPUT_PULLUP);
  pinMode(INPUT3_PIN, INPUT_PULLUP);
  pinMode(UP_BTN_PIN, INPUT);
  pinMode(DOWN_BTN_PIN, INPUT);
  pinMode(OK_BTN_PIN, INPUT);

  // configure LED PWM functionalitites
  ledcSetup(STATUS_LED_CHANEL, STATUS_LED_PWM_FREQ, STATUS_LED_PWM_RESOLUTION);
  ledcAttachPin(STATUS_LED_PIN, STATUS_LED_CHANEL);

  for (;;) {
    lampAgentLoop();
    update_io();
    statusLedLoop();
    if(digitalRead(UP_BTN_PIN) == LOW || digitalRead(DOWN_BTN_PIN) == LOW || digitalRead(OK_BTN_PIN) == LOW){
      lastPressedButtonTime = millis();
      doBeep(0);
    }
    vTaskDelay(pdMS_TO_TICKS(4));
  }
}
