#include <ArduinoOTA.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//#include "LCD03.h"


// WiFi Parameters
const char* ssid = "RigeleFibre";
const char* password = "9977553311";
//LCD03 lcd(0x3F);
//LiquidCrystal_I2C lcd(0x3F,20,4);
LiquidCrystal_I2C lcd1(0x22,20,4);
LiquidCrystal_I2C lcd2(0x20,20,4);
int resetcnt = 0;


void(* resetFunc) (void) = 0;

void updateBothScreens(String line1, String line2, String line3, String line4) {
  lcd1.clear();
  lcd2.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(line1);
  lcd1.setCursor(0, 1);
  lcd1.print(line2);
  lcd1.setCursor(0, 2);
  lcd1.print(line3);
  lcd1.setCursor(0, 3);
  lcd1.print(line4);
  lcd2.setCursor(0, 0);
  lcd2.print(line1);
  lcd2.setCursor(0, 1);
  lcd2.print(line2);
  lcd2.setCursor(0, 2);
  lcd2.print(line3);
  lcd2.setCursor(0, 3);
  lcd2.print(line4);
}


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  lcd1.init(); // initialize the lcd
  lcd2.init();
  lcd1.backlight();
  lcd2.backlight();
 
  lcd1.print("Table 35");
  lcd2.print("Table 36");

  delay(1000);
  Serial.println("Connecting...");


  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    updateBothScreens("Connecting Network", "", "", "");
    resetcnt++;
    if (resetcnt > 10) {
      updateBothScreens("Resettting....", "", "", "");
      resetFunc();
    }
  }
  updateBothScreens("Connected", "", "", "");


  lcd1.clear();
  lcd2.clear();

  ArduinoOTA.setHostname("p2d3");
  ArduinoOTA.setPassword("idiot");


  ArduinoOTA.onStart([]() {
    Serial.println("Start");
    updateBothScreens("SW Upgrade started", "", "Please wait", "");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    updateBothScreens("SW Upgrade", "", "" + (progress / (total / 100)), "");
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("OTA ready");

}

void loop() {
  // Check WiFi Status


  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;  //Object of class HTTPClient
    updateBothScreens("Getting Data", "", "", "");
    // Send request
    http.useHTTP10(true);
    http.begin("http://192.168.99.20:5001/api/v1/screens_1_2");
    Serial.println("Sending request");
    int httpCode = http.GET();

    if (httpCode > 0) {
      // Parse response
      DynamicJsonDocument doc(2048);
      deserializeJson(doc, http.getStream());
      Serial.println("Deserialized Document...");

      // Parameters
      //lcd.noBacklight();
      for (JsonObject elem : doc.as<JsonArray>()) {

        Serial.println("Decoded Element ...");
        // Serial.println(elem);
        const char* site_id = elem["site_id"]; // "1", "1", "1", "1", "1", "1"
        const char* plant_id = elem["plant_id"]; // "2", "2", "2", "2", "2", "2"
        const char* rpr_table_id = elem["rpr_table_id"]; // "1", "2", "3", "4", "5", "6"
        const char* line1 = elem["line1"]; // "Today: 36", "Today: 8", "Today: 39", "Today: 5", "Today: 36", ...
        const char* line2 = elem["line2"]; // "Target: 130", "Target: 130", "Target: 130", "Target: 144", ...
        const char* line3 = elem["line3"]; // "Hello", "Hello", "Hello", "Hello", "Hello", ...
        const char* line4 = elem["line4"]; // "World", "World", "World", "World", "World", ...


        //Serial.println(rpr_table_id);

        if (strcmp(rpr_table_id, "35") == 0) {
          lcd1.clear();
          //  lcd.home();
          lcd1.setCursor(0, 0);
          lcd1.print(line1);
          lcd1.setCursor(0, 1);
          lcd1.print(line2);
          lcd1.setCursor(0, 2);
          lcd1.print(line3);
          lcd1.setCursor(0, 3);
          lcd1.print(line4);

        }

        if (strcmp(rpr_table_id, "36") == 0) {

          lcd2.clear();
          //  lcd.home();
          lcd2.setCursor(0, 0);
          lcd2.print(line1);
          lcd2.setCursor(0, 1);
          lcd2.print(line2);
          lcd2.setCursor(0, 2);
          lcd2.print(line3);
          lcd2.setCursor(0, 3);
          lcd2.print(line4);

        }


      }
    }
    else {
      updateBothScreens("Failed to Get Data", "", "Error:", http.errorToString(httpCode).c_str());
    }
    http.end();   //Close connection
    ArduinoOTA.handle();
  }
  else {
    updateBothScreens("No Network", "", "Reconnecting", "");
    WiFi.reconnect();
    resetcnt++;
    if (resetcnt > 3) {
      updateBothScreens("Reseting....", "", "", "");
      resetFunc();
    }


  }
  // Delay
  delay(10000);
}
