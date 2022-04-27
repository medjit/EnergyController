#include <WiFi.h>
#include <PubSubClient.h>

// MQTT Broker
char *mqtt_broker = ENERGY_CONTROLLER_MQTT_BROKER;
char *topic = "kusak/solar/ping";
char *mqtt_username = ENERGY_CONTROLLER_MQTT_USERNAME;
char *mqtt_password = ENERGY_CONTROLLER_MQTT_PASSWORD;
int mqtt_port = ENERGY_CONTROLLER_MQTT_PORT;

WiFiClient espClient;
PubSubClient client(espClient);


void callback(char *topic, byte *payload, unsigned int length) {
    TelnetStream.print("Message arrived in topic: ");
    TelnetStream.println(topic);
    TelnetStream.print("Message:");
    for (int i = 0; i < length; i++) {
        TelnetStream.print((char) payload[i]);
    }
    TelnetStream.println();
    TelnetStream.println("-----------------------");
}


void mqtt_task(void * parameter){
  //connecting to a mqtt broker
  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(pdMS_TO_TICKS(500));
  }
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
      String client_id = "esp32-client-";
      client_id += String(WiFi.macAddress());
      TelnetStream.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
      if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
          TelnetStream.println("Public emqx mqtt broker connected");
      } else {
          TelnetStream.print("failed with state ");
          TelnetStream.print(client.state());
          vTaskDelay(pdMS_TO_TICKS(2000));
      }
  }
  // publish and subscribe
  client.publish(topic, "Hi kusak solar and ESP32 ^^");
  //client.subscribe(topic);

  for (;;) {
    String message = (String)uptime();
    client.publish(topic, message.c_str());
    vTaskDelay(pdMS_TO_TICKS(1000));
    client.loop();
  }
}
