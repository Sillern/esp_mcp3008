/*
  MCP3008.h - Library for communicating with MCP3008 Analog to digital converter.
  Created by Uros Petrevski, Nodesign.net 2013
  Released into the public domain.

  ported from Python code originaly written by Adafruit learning system for rPI :
  http://learn.adafruit.com/send-raspberry-pi-data-to-cosm/python-script

  Converted to work with ESP8266 by Sebastian Jegerås 2016.
*/

#ifndef MCP3008_h
#define MCP3008_h

void MCP3008_init();
int MCP3008_readADC(int adcnum);


#endif
