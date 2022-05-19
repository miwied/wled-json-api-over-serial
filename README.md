# wled-json-api-over-serial
This is a very simple example code of how to work with the wled json api over serial. It sets a random color when pushing a button on the sending-mcu.

***Test-Setup:***
- Sending-µC: esp32 
- Recieving-µC: esp8266
- wled version: "WLED-0.13.0-b6"
- baud rate: 115200 
- tested baudrates: 115200, 230400, 460800, 500000, 921600, 1000000, 1500000

***Connections:***
- esp32 pin 2(RX) <-> esp8266 pin 1(TX)
- esp32 pin 4(TX) <-> esp8266 pin 3(RX)
- esp32 gnd <-> esp8266 gnd
