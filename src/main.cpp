/*
This code is just for testing the wled json api over serial.
Sending-µC is a esp32 and recieving-µC is a esp8266 with a custom compiled wled (WLED-0.13.0-b6) with a serial baudrate of 115200.

connections:
esp32 pin 2(RX) <-> esp8266 pin 1(TX)
esp32 pin 4(TX) <-> esp8266 pin 3(RX)
esp32 gnd <-> esp8266 gnd
*/

#include "Arduino.h"
#include "ArduinoJson.h"

HardwareSerial wledSerial(1);

void jsonRequest()
{
  StaticJsonDocument<16> doc;
  doc["v"] = true;
  serializeJson(doc, wledSerial);
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

  serializeJson(doc, wledSerial);
}

void setup() 
{
  Serial.begin(115200); //serial monitor

  //the baudrate of 115200 worked perfectly for me
  wledSerial.begin(115200, SERIAL_8N1, 2, 4); //tested baudrates: 115200, 230400, 460800, 500000, 921600, 1000000, 1500000

  pinMode(15, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() 
{
  //change color on button press
  if(digitalRead(15)==LOW)
  {
    sendRGB(random(0, 254), random(0, 254), random(0, 254));
    delay(250);
    
    jsonRequest();
  }

  //response from wled controller
  if(wledSerial.available()>0)
  {
   Serial.write(wledSerial.read());
  }
}

