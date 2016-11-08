# esp_mcp3008

ESP8266 module for reading data from an MCP3008

It's built on top of [tuanpmt's esp_mqtt project](https://github.com/tuanpmt/esp_mqtt).
The MCP interface is ported from [Uros Petrevskis arduino code](https://github.com/nodesign/MCP3008)

##Usage
At start, run the init function.
MCP3008_init();

Run MCP3008_readADC(int adcnum) to get the value from a channel.

### Pin configuraton


MCP3008 | ESP8266
-------|------------------
DGND pin 9 | GND
CS Pin 10 | GPIO3
MISO Pin 11 | GPIO12
MOSI  Pin 12 | GPIO13
CLK Pin 13 | GPIO14
AGND Pin 14 | VDD
VREF Pin 15 | VDD
VDD Pin 16 | VDD

All of the pins are configurable, you just set the pins you want to use in the setting struct.

###Building and installing:

Clone the [esp_mqtt](https://github.com/tuanpmt/esp_mqtt) repo and copy the modules directory of this repo to the root directory of that repo.

Please refer to [esp_mqtt](https://github.com/tuanpmt/esp_mqtt) on how to build etc.

I have tested this on an [olimex MOD-WIFI-ESP8266-DEV](https://github.com/OLIMEX/ESP8266/tree/master/HARDWARE/MOD-WIFI-ESP8266-DEV) with esp open sdk 1.5.4
