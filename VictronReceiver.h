#define RXD2 16
#define TXD2 17

void victron_task(void * parameter){
  Serial1.begin(19200, SERIAL_8N1, RXD2, TXD2);
  Serial1.setRxBufferSize(400);
  
  for (;;) {
    String victron_data = "";
    while(Serial1.available()){
      char c = Serial1.read();
      victron_data += c;
    }
    TelnetStream.println(victron_data);
    vTaskDelay(pdMS_TO_TICKS(950));
  }
}
