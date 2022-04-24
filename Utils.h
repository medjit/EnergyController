void doBeep(byte type){
  switch(type){
    case 0:
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(pdMS_TO_TICKS(30));
      digitalWrite(BUZZER_PIN, LOW);
      break;
    case 1:
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(pdMS_TO_TICKS(100));
      digitalWrite(BUZZER_PIN, LOW);
      break;
    case 2:
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(pdMS_TO_TICKS(30));
      digitalWrite(BUZZER_PIN, LOW);
      vTaskDelay(pdMS_TO_TICKS(100));
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(pdMS_TO_TICKS(30));
      digitalWrite(BUZZER_PIN, LOW);
      break;
    case 3:
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(pdMS_TO_TICKS(1500));
      digitalWrite(BUZZER_PIN, LOW);
      break;
    default:
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(pdMS_TO_TICKS(1000));
      digitalWrite(BUZZER_PIN, LOW);
  }
}
