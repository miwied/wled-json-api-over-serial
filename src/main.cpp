//this code sends simple control-json packets to a esp8266 with wled
#include "Arduino.h"
#include "ArduinoJson.h"
#include "SoftwareSerial.h"

SoftwareSerial wledOut(2, 4); //rx, tx

void sendJson(int color) //16-Bit color value
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(10);

  int r = ((((color >> 11) & 0x1F) * 527) + 23) >> 6;
  int g = ((((color >> 5) & 0x3F) * 259) + 33) >> 6;
  int b = (((color & 0x1F) * 527) + 23) >> 6;

  StaticJsonDocument<192> doc;

  doc["on"] = true;
  doc["bri"] = 100;
  doc["ps"] = -1;

  JsonObject seg_0 = doc["seg"].createNestedObject();

  JsonArray seg_0_col_0 = seg_0["col"].createNestedArray();
  seg_0_col_0.add(r);
  seg_0_col_0.add(g);
  seg_0_col_0.add(b);
  seg_0["fx"] = 0;

  serializeJson(doc, wledOut);

  digitalWrite(LED_BUILTIN, LOW);
  delay(10);
}



void setup() 
{
  Serial.begin(115200);
  wledOut.begin(921600);
  
  pinMode(15, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}


void loop() 
{
  if(digitalRead(15)==LOW)
  {
    sendJson(13875); //türkis
    delay(250);
  }
  delay(1000);
  sendJson(13875); //türkis
  delay(5000);
  sendJson(39156); //lila
  delay(5000);
  sendJson(63488); //rot
  delay(5000);
  sendJson(65535); //weiss
  delay(5000);
}

