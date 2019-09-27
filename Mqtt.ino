#include <WiFi.h>
#include <PubSubClient.h>

extern const char* ssid;
extern const char* password;
extern const int port;
extern const char* topic;
extern const char* server;
WiFiClient espClient;
PubSubClient mqttClient(espClient);
const char* clientId = topic + millis() + random(1000,100000);

void connectToWifi(){
//  Serial.println("Mqtt - connectToWifi");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Trying to connect wifi...Please wait.");
    delay(2000);
  }
  Serial.println("Connected to the WiFi network");
}

void connectToMQTT(){
//  Serial.println("Mqtt - connectToMQTT");

  mqttClient.setServer(server, port);
  delay(2000);
  
  while (!mqttClient.connected()) {
    Serial.println("Trying to connect server...Please wait.");
    if (mqttClient.connect(clientId)) {
      Serial.println("connected to the server");
    } else {
      Serial.printf("failed, rc = %d \n",mqttClient.state());
      Serial.println("Retrying in 2 seconds");
      delay(2000);
    }
  }
  publish(topic, sampleJson);
}

boolean publish(const char* topic, const char* message){
    Serial.println(message);
    int i = 0;
    boolean rc = mqttClient.publish(topic, message);
    while(i != 10 && !rc){
      Serial.printf("publish failed on \"%s\"...retrying [%d/10]\n", topic, i);
      rc =  mqttClient.publish(topic, message);
      delayMicroseconds(2000);
      i++;
    }
    return rc;
}

void detectTouch(void * pvParameters) {
//  Serial.println("Mqtt - detectTouch");
    while(1){
      if(!mqttClient.connected()){
          connectToWifi();
          connectToMQTT(); 
          restore();
      }
      mqttClient.loop();
    }  
}
