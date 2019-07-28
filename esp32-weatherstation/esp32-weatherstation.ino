#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <PubSubClient.h>

#include "settings.h"
#include "MCUFRIEND_UI.h"

#include <Fonts/FreeSansBold12pt7b.h>

// UI is scaled for a display of 480x320

String temperature = "22.00";
String humidity = "35.00";
String remoteTemperature = "22.00";
String remoteHumidity = "35.00";

String timeStamp;
boolean mqttOn;

class HeaderPanel : public Panel {
  protected:
    void renderContentWithin(uint16_t xLoc, uint16_t yLoc, uint16_t width, uint16_t height) {

      tft->setTextSize(2);

      tft->setTextColor(WHITE, DARK_GREEN);
      if (WiFi.status() == WL_CONNECTED) {
        tft->setCursor(5, 2);
        tft->print("Online ");
        tft->setCursor(165, 2);
        tft->print(WiFi.localIP());
      } else {
        tft->setCursor(5, 2);
        tft->println("Offline");
      }

      if (mqttOn) {
        tft->setCursor(100,2);
        tft->print("MQTT");
      } else {
        tft->setTextColor(DARK_GREEN);
        tft->setCursor(100,2);
        tft->print("MQTT");
      }

      tft->setTextColor(WHITE, DARK_GREEN);
      tft->setCursor(380, 2);
      tft->println(timeStamp);
    }
};

class Panel1 : public Panel {
  protected:
    void renderContentWithin(uint16_t xLoc, uint16_t yLoc, uint16_t width, uint16_t height) {

      tft->setTextColor(WHITE, ORANGE);  
      tft->setCursor(100, 37);
      tft->print("LOCAL");
    
      tft->setCursor(35, 133);
      tft->setFont(&FreeSansBold12pt7b);
      tft->print(temperature);
      tft->print("*C");
    
      tft->setCursor(25, 165);
      tft->setFont();
      tft->print("Humidity:");
      tft->print(humidity);      
      tft->print("%");
    }
};

class Panel2 : public Panel {
  protected:
    void renderContentWithin(uint16_t xLoc, uint16_t yLoc, uint16_t width, uint16_t height) {

      tft->setTextColor(WHITE, METAL_BLUE);  
      tft->setCursor(320, 37);
      tft->print("REPORTED");
    
      tft->setCursor(265, 133);
      tft->setFont(&FreeSansBold12pt7b);
      tft->print(remoteTemperature);
      tft->print("*C");
    
      tft->setCursor(265, 165);
      tft->setFont();
      tft->print("Humidity:");
      tft->print(remoteHumidity);
      tft->print("%");
    }
};

class Panel3 : public Panel {
  protected:
    void renderContentWithin(uint16_t xLoc, uint16_t yLoc, uint16_t width, uint16_t height) {

      tft->setTextColor(WHITE, PALE_RED);  

      tft->setCursor(30, 230);
      tft->print("EXTRAS");

      tft->setCursor(40, 261);
      tft->print("No warnings or other special info.");
    }
};

WiFiClient espClient;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
PubSubClient client(espClient);

MCUFRIEND_kbv tft;
UI ui(&tft);
HeaderPanel header;
Panel1 panel1;
Panel2 panel2;
Panel3 panel3;  

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

    if (WiFi.status() == WL_CONNECTED) { 
      client.setServer(MQTT_HOST, MQTT_PORT);
      client.setCallback(updateLocalWeather);
      if (client.connect("WeatherStation", MQTT_USER, MQTT_PASS)) {
        client.subscribe(MQTT_TOPIC_T);
        client.subscribe(MQTT_TOPIC_H);
        client.subscribe(MQTT_TOPIC_RT);
        client.subscribe(MQTT_TOPIC_RH);
        mqttOn = true;
      } else {
        mqttOn = false;
      }
    } else {
      mqttOn = false;
    }
  }
}

void updateTime() {

  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }  
  String formattedDate = timeClient.getFormattedTime();
  int splitT = formattedDate.indexOf("T");
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length());
}

void updateLocalWeather(char* topic, byte* message, unsigned int length) {

  String topicStr = String(topic);
  String messageTemp = "";
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }  

  Serial.println(topicStr);
  
  if (topicStr.equals(MQTT_TOPIC_T)) {
    temperature = messageTemp;
  } else if (topicStr.equals(MQTT_TOPIC_H)) {
    humidity = messageTemp;
  } else if (topicStr.equals(MQTT_TOPIC_RT)) {
    remoteTemperature = messageTemp;
  } else {
    remoteHumidity = messageTemp;
  }
}

long weatherLastUpdated;

void loop() {

  connectIfNeeded();
  updateTime();
  client.loop();

  //if (millis() - weatherLastUpdated > 5000) {
  if (weatherLastUpdated > 10) {
    panel1.render();
    panel2.render();  
    //weatherLastUpdated = millis();
    weatherLastUpdated = 0;
  }

  header.renderContent();

  delay(500);
  weatherLastUpdated++;
}

void setup() {

  Serial.begin(9600);

  header.setup(0, 0, 630, 20, 5, DARK_GREEN);
  panel1.setup(10, 25, 230, 185, 10, ORANGE);
  panel2.setup(250, 25, 220, 185, 10, METAL_BLUE);
  panel3.setup(10, 220, 460, 90, 10, PALE_RED);  

  ui.setup();
  ui.add(&header);
  ui.add(&panel1);
  ui.add(&panel2);
  ui.add(&panel3);

  ui.render();

  connectIfNeeded();
  timeClient.begin();
  timeClient.setTimeOffset(7200);
}
