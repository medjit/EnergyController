#include <WiFi.h>
#include <PubSubClient.h>

// MQTT Broker
char *mqtt_broker = ENERGY_CONTROLLER_MQTT_BROKER;
char *mqtt_username = ENERGY_CONTROLLER_MQTT_USERNAME;
char *mqtt_password = ENERGY_CONTROLLER_MQTT_PASSWORD;
int mqtt_port = ENERGY_CONTROLLER_MQTT_PORT;

WiFiClient espClient;
PubSubClient client(espClient);

void publish_value(String vendor_topic, data_field_t *field_ptr){
  data_field_t *field = (data_field_t*)field_ptr;
  String value = (String)field->value;
  field->flags.mqtt = false;
  String final_topic = vendor_topic + field->field_topic;
  client.publish(final_topic.c_str(), value.c_str());
}

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

void send_ve_data(){
  if(ve_data.panel_voltage.flags.mqtt)      publish_value(ve_data.vendor_topic, &ve_data.panel_voltage);
  if(ve_data.battery_voltage.flags.mqtt)    publish_value(ve_data.vendor_topic, &ve_data.battery_voltage);
  if(ve_data.battery_current.flags.mqtt)    publish_value(ve_data.vendor_topic, &ve_data.battery_current);
  if(ve_data.power.flags.mqtt)              publish_value(ve_data.vendor_topic, &ve_data.power);
  if(ve_data.yield_total.flags.mqtt)        publish_value(ve_data.vendor_topic, &ve_data.yield_total);
  if(ve_data.yield_today.flags.mqtt)        publish_value(ve_data.vendor_topic, &ve_data.yield_today);
  if(ve_data.max_pwr_today.flags.mqtt)      publish_value(ve_data.vendor_topic, &ve_data.max_pwr_today);
  if(ve_data.yield_yesterday.flags.mqtt)    publish_value(ve_data.vendor_topic, &ve_data.yield_yesterday);
  if(ve_data.max_pwr_yesterday.flags.mqtt)  publish_value(ve_data.vendor_topic, &ve_data.max_pwr_yesterday);
  if(ve_data.charger_state.flags.mqtt)      publish_value(ve_data.vendor_topic, &ve_data.charger_state);
}

void send_board_data(){
  //TODO:
}

void send_data_to_broker(){
  String client_id = "esp32-client-";
  client_id += String(WiFi.macAddress());
  if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      TelnetStream.println("Mqtt broker connected");
      send_ve_data();
      send_board_data();
  } else {
      TelnetStream.print("failed with state ");
      TelnetStream.print(client.state());
      vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void mqtt_task(void * parameter){
  //set topics
  ve_data.panel_voltage.field_topic =     "/panelvoltage";
  ve_data.battery_voltage.field_topic =   "/batteryvoltage";
  ve_data.battery_current.field_topic =   "/batterycurrent";
  ve_data.power.field_topic =             "/power";
  ve_data.yield_total.field_topic =       "/yieldtotal";
  ve_data.yield_today.field_topic =       "/yieldtoday";
  ve_data.max_pwr_today.field_topic =     "/maxtoday";
  ve_data.yield_yesterday.field_topic =   "/yieldyesterday";
  ve_data.max_pwr_yesterday.field_topic = "/maxyesterday";
  ve_data.charger_state.field_topic =     "/chargerstate";

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

  //client.subscribe(topic);

  for (;;) {
    //String message = (String)uptime();
    //client.publish(topic, message.c_str());
    send_data_to_broker();
    client.loop();
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}
