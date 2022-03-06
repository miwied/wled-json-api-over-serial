/*
This code is just for testing the json api over serial.
Sending µC is a esp32 and recieving µC is a esp8266 with a custom compiled wled (WLED-0.13.0-b6) with a serial baudrate of 921600.
This code did work a few days ago, but sometimes it had like a input lag. Now unfortunately the receive problem occurs much more frequently

connections:
esp32 pin 2(RX) <-> esp8266 pin 1(TX)
esp32 pin 4(TX) <-> esp8266 pin 3(RX)
esp32 gnd <-> esp8266 gnd
*/

#include "Arduino.h"
#include "ArduinoJson.h"
#include "SoftwareSerial.h"

SoftwareSerial wledOut(2, 4); //rx, tx

void randomColor() 
{
  StaticJsonDocument<192> doc;

  doc["on"] = true;
  doc["bri"] = 110;

  JsonArray seg_0_col_0 = doc["seg"][0]["col"].createNestedArray();
  seg_0_col_0.add(random(0, 254));
  seg_0_col_0.add(random(0, 254));
  seg_0_col_0.add(random(0, 254));

  // serializeJson(doc, Serial); //print json to Serial for debugging
  for(int i = 0; i<2; i++)
  {
  serializeJson(doc, wledOut);
  wledOut.println('\n');
  }
  // Serial.println("");
}

void sendRGB(int r, int g, int b) 
{
  StaticJsonDocument<192> doc;
  doc["on"] = true;
  doc["bri"] = 110;

  JsonArray seg_0_col_0 = doc["seg"][0]["col"].createNestedArray();
  seg_0_col_0.add(r);
  seg_0_col_0.add(g);
  seg_0_col_0.add(b);

  // serializeJson(doc, Serial); //print json to Serial for debugging 
  for(int i = 0; i<6; i++)
  {
  serializeJson(doc, wledOut);
  wledOut.println('\n');
  }
}

void setup() 
{
  Serial.begin(115200); //serial monitor
  wledOut.begin(921600); //tested baudrates: 115200, 230400, 460800, 500000,  921600, 1000000, 1500000

  pinMode(15, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() 
{
  if(digitalRead(15)==LOW)
  {
    sendRGB(random(0, 254), random(0, 254), random(0, 254));
    // randomColor();
    delay(250);
  }

  // randomColor(); //should change the color once a second -> sometimes it dont! :(
  // delay(1000);
}

