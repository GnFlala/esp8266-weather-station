/**The MIT License (MIT)

Copyright (c) 2016 by Count023 -> https://github.com/count023

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <JsonListener.h>
#include "WundergroundConditions.h"

/**
 * Wunderground Settings
 */
const String  WUNDERGRROUND_API_KEY = "808ba87ed77c4501";
const boolean IS_METRIC = true;
const boolean USE_PM = false;
// to retrieve the ZMW-Code use
// 		http://api.wunderground.com/api/<API-KEY>/conditions/q/<COUNTRY-CODE>/<CITY-NAME>.json
// for example and grab for the zmw ...
const String  WUNDERGROUND_ZMW_CODE = "00000.215.10348"; // Braunschweig-Flughafen -> EDVE
const String  WUNDERGRROUND_LANGUAGE = "DE";

// initiate the WundergoundClient
WundergroundConditions wunderground(IS_METRIC, USE_PM);


/**
 * WiFi Settings
 */
const char* ESP_HOST_NAME = "esp-" + ESP.getFlashChipId();
const char* WIFI_SSID     = "yourssid";
const char* WIFI_PASSWORD = "yourpassw0rd";

// initiate the WifiClient
WiFiClient wifiClient;



/**
 * Helping funtions
 */
void connectWifi() {
  WiFi.hostname(ESP_HOST_NAME);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  delay(20);
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.println(WiFi.localIP());
  Serial.println();
}


/**
 * SETUP
 */
void setup() {

  Serial.begin(115200);

  connectWifi();

  Serial.println();
  Serial.println("\n\nNext Loop-Step: " + String(millis()) + ":");

  wunderground.updateConditions(WUNDERGRROUND_API_KEY, WUNDERGRROUND_LANGUAGE, WUNDERGROUND_ZMW_CODE);

  Serial.println("wundergroundDate: " + wunderground.getDate());

  Serial.println("wundergroundWindSpeed: " + wunderground.getWindSpeed());
  Serial.println("wundergroundWindDir: " + wunderground.getWindDir());

  Serial.println("wundergroundCurrentTemp: " + wunderground.getCurrentTemp());
  Serial.println("wundergroundTodayIcon: " + wunderground.getTodayIcon());
  Serial.println("wundergroundTodayIconText: " + wunderground.getTodayIconText());
  Serial.println("wundergroundMeteoconIcon: " + wunderground.getMeteoconIcon(wunderground.getTodayIconText()));
  Serial.println("wundergroundWeatherText: " + wunderground.getWeatherText());
  Serial.println("wundergroundHumidity: " + wunderground.getHumidity());
  Serial.println("wundergroundPressure: " + wunderground.getPressure());
  Serial.println("wundergroundDewPoint: " + wunderground.getDewPoint());
  Serial.println("wundergroundPrecipitationToday: " + wunderground.getPrecipitationToday());

  Serial.println();
  Serial.println("---------------------------------------------------/\n");

}


/**
 * LOOP
 */
void loop() {

}
