#include <DHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "settings.h"

WiFiClient espClient;
PubSubClient client(espClient); 

#define REPORT_DELAY_SECS 30

DHT dht22(D2, DHT22);

void setup() {
  
  Serial.begin(9600);
  dht22.begin();
}

void loop() {

  connectIfNeeded();
  client.loop(); 

  float h2 = dht22.readHumidity();
  float t2 = dht22.readTemperature();
  if (isnan(h2) || isnan(t2)) {
    return;
  }
  client.publish(MQTT_TOPIC_H, String(h2).c_str(), false);
  client.publish(MQTT_TOPIC_T, String(t2).c_str(), false); 

  delay(REPORT_DELAY_SECS * 1000);
}

void connectIfNeeded() {

  int tries = 3;

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("(Re)connecting WiFi...");
    do {
      WiFi.mode(WIFI_STA);
      WiFi.disconnect();
      WiFi.begin(WIFI_SSID, WIFI_PASS);
      WiFi.setAutoConnect(true);
      WiFi.setAutoReconnect(true);
      delay(1000);
      Serial.print("Tries left: ");
      Serial.println(tries);
      tries--;
    } while (WiFi.status() != WL_CONNECTED && tries > 0);
  }

  if (WiFi.status() == WL_CONNECTED) { 
    client.setServer(MQTT_HOST, MQTT_PORT);
    if (client.connect("ESP8266-dht22", MQTT_USER, MQTT_PASS)) {
      Serial.println("Connected.");    
    }
  }
}
