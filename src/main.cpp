//this code sends simple control-json packets to a esp8266 with wled
#include "Arduino.h"
#include "ArduinoJson.h"
#include "SoftwareSerial.h"

SoftwareSerial wledOut(2, 4); //rx, tx

void sendJson(int color) //16-Bit color value
{
  // digitalWrite(LED_BUILTIN, HIGH);
  // delay(10);

  int r = ((((color >> 11) & 0x1F) * 527) + 23) >> 6;
  int g = ((((color >> 5) & 0x3F) * 259) + 33) >> 6;
  int b = (((color & 0x1F) * 527) + 23) >> 6;

for(int i = 0; i < 3; i++)
  {
    StaticJsonDocument<192> doc;

    doc["on"] = true;
    doc["bri"] = 110;
    doc["ps"] = -1;

    JsonObject seg_0 = doc["seg"].createNestedObject();

    JsonArray seg_0_col_0 = seg_0["col"].createNestedArray();
    seg_0_col_0.add(r);
    seg_0_col_0.add(g);
    seg_0_col_0.add(b);
    seg_0["fx"] = 0;


    serializeJson(doc, wledOut);
    delay(2);
  }

  // digitalWrite(LED_BUILTIN, LOW);
  // delay(10);
}

void testLight()
{
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
    Serial.println("push!");
    delay(250);
    StaticJsonDocument<16> doc;
    doc["v"] = true;
    serializeJson(doc, wledOut);
  }

if (Serial.available() > 0)
  {
    Serial.println("serial available!");
  }

  if (wledOut.available() > 0)
  {
    Serial.println("wled serial available!");
    // wledOut.setTimeout(100);
    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, wledOut);
    if(error) 
    {
      Serial.println("wled serial error!");
      return;
    }
    JsonObject state = doc["state"];
    bool state_on = state["on"]; // true
    int state_bri = state["bri"]; // 135
    int state_transition = state["transition"]; // 7
    int state_ps = state["ps"]; // -1
    int state_pl = state["pl"]; // -1

    JsonObject state_nl = state["nl"];
    bool state_nl_on = state_nl["on"]; // false
    int state_nl_dur = state_nl["dur"]; // 60
    int state_nl_mode = state_nl["mode"]; // 1
    int state_nl_tbri = state_nl["tbri"]; // 0
    int state_nl_rem = state_nl["rem"]; // -1

    bool state_udpn_send = state["udpn"]["send"]; // false
    bool state_udpn_recv = state["udpn"]["recv"]; // true

    int state_lor = state["lor"]; // 0
    int state_mainseg = state["mainseg"]; // 0

    JsonObject state_seg_0 = state["seg"][0];
    int state_seg_0_id = state_seg_0["id"]; // 0
    int state_seg_0_start = state_seg_0["start"]; // 0
    int state_seg_0_stop = state_seg_0["stop"]; // 16
    int state_seg_0_len = state_seg_0["len"]; // 16
    int state_seg_0_grp = state_seg_0["grp"]; // 1
    int state_seg_0_spc = state_seg_0["spc"]; // 0
    int state_seg_0_of = state_seg_0["of"]; // 0
    bool state_seg_0_on = state_seg_0["on"]; // true
    int state_seg_0_bri = state_seg_0["bri"]; // 255
    int state_seg_0_cct = state_seg_0["cct"]; // 127

    JsonArray state_seg_0_col = state_seg_0["col"];

    JsonArray state_seg_0_col_0 = state_seg_0_col[0];
    int state_seg_0_col_0_0 = state_seg_0_col_0[0]; // 255
    int state_seg_0_col_0_1 = state_seg_0_col_0[1]; // 255
    int state_seg_0_col_0_2 = state_seg_0_col_0[2]; // 255
    int state_seg_0_col_0_3 = state_seg_0_col_0[3]; // 0

    JsonArray state_seg_0_col_1 = state_seg_0_col[1];
    int state_seg_0_col_1_0 = state_seg_0_col_1[0]; // 0
    int state_seg_0_col_1_1 = state_seg_0_col_1[1]; // 0
    int state_seg_0_col_1_2 = state_seg_0_col_1[2]; // 0
    int state_seg_0_col_1_3 = state_seg_0_col_1[3]; // 0

    JsonArray state_seg_0_col_2 = state_seg_0_col[2];
    int state_seg_0_col_2_0 = state_seg_0_col_2[0]; // 0
    int state_seg_0_col_2_1 = state_seg_0_col_2[1]; // 0
    int state_seg_0_col_2_2 = state_seg_0_col_2[2]; // 0
    int state_seg_0_col_2_3 = state_seg_0_col_2[3]; // 0

    int state_seg_0_fx = state_seg_0["fx"]; // 0
    int state_seg_0_sx = state_seg_0["sx"]; // 128
    int state_seg_0_ix = state_seg_0["ix"]; // 128
    int state_seg_0_pal = state_seg_0["pal"]; // 0
    bool state_seg_0_sel = state_seg_0["sel"]; // true
    bool state_seg_0_rev = state_seg_0["rev"]; // false
    bool state_seg_0_mi = state_seg_0["mi"]; // false

    JsonObject info = doc["info"];
    const char* info_ver = info["ver"]; // "0.13.0-b6"
    long info_vid = info["vid"]; // 

    JsonObject info_leds = info["leds"];
    int info_leds_count = info_leds["count"]; // 16
    bool info_leds_rgbw = info_leds["rgbw"]; // true
    bool info_leds_wv = info_leds["wv"]; // true
    bool info_leds_cct = info_leds["cct"]; // false
    int info_leds_pwr = info_leds["pwr"]; // 580
    int info_leds_fps = info_leds["fps"]; // 3
    int info_leds_maxpwr = info_leds["maxpwr"]; // 850
    int info_leds_maxseg = info_leds["maxseg"]; // 16

    bool info_str = info["str"]; // false
    const char* info_name = info["name"]; // "WLED"
    int info_udpport = info["udpport"]; // 21324
    bool info_live = info["live"]; // false
    const char* info_lm = info["lm"]; // nullptr
    const char* info_lip = info["lip"]; // nullptr
    int info_ws = info["ws"]; // 0
    int info_fxcount = info["fxcount"]; // 118
    int info_palcount = info["palcount"]; // 71

    JsonObject info_wifi = info["wifi"];
    const char* info_wifi_bssid = info_wifi["bssid"]; //
    int info_wifi_rssi = info_wifi["rssi"]; // -68
    int info_wifi_signal = info_wifi["signal"]; // 64
    int info_wifi_channel = info_wifi["channel"]; // 11

    JsonObject info_fs = info["fs"];
    int info_fs_u = info_fs["u"]; // 32
    int info_fs_t = info_fs["t"]; // 1024
    int info_fs_pmt = info_fs["pmt"]; // 0

    int info_ndc = info["ndc"]; // 0
    const char* info_arch = info["arch"]; // "esp8266"
    const char* info_core = info["core"]; // "2_7_4_7"
    int info_lwip = info["lwip"]; // 1
    int info_freeheap = info["freeheap"]; // 20776
    int info_uptime = info["uptime"]; // 158
    int info_opt = info["opt"]; // 127
    const char* info_brand = info["brand"]; // "WLED"
    const char* info_product = info["product"]; // "FOSS"
    const char* info_mac = info["mac"]; // 
    const char* info_ip = info["ip"]; // 

    char buffer[2048];
    serializeJson(doc, buffer);
  }

}

