# DIY Weather Station Project
This repository holds all the source code for my weather station project. Note: it's heavily work in progress!

# Prerequisites

 - Obviously you'll need some hardware (watch the video here: https://youtu.be/ILWRXSZ0rN0)
 - You need Arduino IDE and the following libraries to be installed: Adafruit GFX, MCUFriend_kbv, PubSubClient
 - You need an MQTT Broker - even some simple one like Mosquitto will do
 - You need a host to run the REST -> MQTT bridge (the easiest way is to have a Docker host)

# Main components

## esp32-weatherstation
Firmware for the ESP32 board with the LCD panel. Unfortunately not just any ESP32 board and LCD panel will do, the code is explicitely written for these:

 - Board - https://bit.ly/2SKlTEs
 - LCD Panel - https://bit.ly/2YbdHmR

## esp8266-tempsensor
A very simple firmware for an ESP8266-based MCU (D1 Mini, NodeMCU 1.0, etc), which only does two things:
 - Reads temperature & humidity data from a DHT22 sensor
 - Pushes the read values to two specified MQTT topics
 
To be honest, this component can be replaced with many things - different board, different sensor, etc. as long as it sends the same data to the same MQTT topics.

## openweathermap-mqtt
A simple backend service written in Java - it's running on Spring Boot and can be deployed for example via Docker. To work properly, you need an application token from OpenWeatherMap, because it fetches data from OpenWeatherMap. See here for more information: https://openweathermap.org/api

Simply put, this service is a REST to MQTT bridge - e.g. it pulls data from OpenWeatherMap via REST, parses it and pushes it to an MQTT broker, so other components can receive it.

# Configuration

Each of the projects holds a "settings.h" (Arduino projects) or an "application.yaml" (the Java based project), which needs to be adjusted to your needs - you'll need to enter things like your WiFi SSID & password, host, username and password for the MQTT broker.
