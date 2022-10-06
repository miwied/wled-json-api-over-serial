
# wled-json-api-over-serial
This is a very simple [example code](https://github.com/miwied/wled-json-api-over-serial/blob/main/src/main.cpp) of how to work with the [WLED](https://github.com/Aircoookie/WLED) json api over serial using [PlatformIO](https://platformio.org/) and the [ArduinoJson library](https://github.com/bblanchon/ArduinoJson).

With the help of the wled json api you are able to use all api commands to control a wled-flashed-mcu with any other serial capable microcontroller. 

In my example sketch by pressing a button which is conntected to the sending-mcu it will change the color of the led-strip on the wled-mcu.

## Setup:
- sending-µC: esp32 
- receiving-µC: esp8266
- wled version: "WLED-0.13.0-b6"
- baud rate: 115200 
- tested baudrates: 115200, 230400, 460800, 500000, 921600, 1000000, 1500000

## Note:
SoftwareSerial is only suitable for very slow baud rates, definitely not 921600. You should always use HardwareSerial if possible, and in case SoftwareSerial is indispensable, use the lowest possible rate.

## Connections:
- esp32 pin 2(RX) <-> esp8266 pin 1(TX)
- esp32 pin 4(TX) <-> esp8266 pin 3(RX)
- esp32 gnd <-> esp8266 gnd
