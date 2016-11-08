/*
  MCP3008.cpp - Library for communicating with MCP3008 Analog to digital converter.
  Created by Uros Petrevski, Nodesign.net 2013
  Released into the public domain.

  ported from Python code originaly written by Adafruit learning system for rPI :
  http://learn.adafruit.com/send-raspberry-pi-data-to-cosm/python-script

  Converted to work with ESP8266 by Sebastian Jegerås 2016.
*/

#include "MCP3008.h"
#include "osapi.h"
#include "os_type.h"
#include "gpio.h"

#define SPI_MISO_PIN 12
#define SPI_MOSI_PIN 13
#define SPI_CLK_PIN  14
#define SPI_CS_PIN   3

#define CLOCK_DELAY 1000
#define CLOCK_STEP() do \
{\
  os_delay_us(CLOCK_DELAY);\
  GPIO_OUTPUT_SET(SPI_CLK_PIN, 1);\
  os_delay_us(CLOCK_DELAY);\
  GPIO_OUTPUT_SET(SPI_CLK_PIN, 0);\
} while (0)\

void MCP3008_init()
{
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12); //GPIO12 is HSPI MISO pin (Master Data In)
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13); //GPIO13 is HSPI MOSI pin (Master Data Out)
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14); //GPIO14 is HSPI CLK pin (Clock)
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0RXD_U, FUNC_GPIO3);
}

// read SPI data from MCP3008 chip, 8 possible adc's (0 thru 7)
int MCP3008_readADC(int channel)
{
  //int i = 0;
  if ((channel > 7) || (channel < 0))
  {
    return -1; // Wrong adc address return -1
  }

  GPIO_OUTPUT_SET(SPI_CS_PIN,  1);
  //# start clock low
  GPIO_OUTPUT_SET(SPI_CLK_PIN, 0);
  //# bring CS low
  GPIO_OUTPUT_SET(SPI_CS_PIN,  0);


  int i = 0;
  //# start bit + single-ended bit
  //# we only need to send 5 bits here
  int commandout = (0x18 | channel) << 3;

  for (i=0; i<5; i++) {
    uint8_t value = (commandout & 0x80) == 0x80;
    GPIO_OUTPUT_SET(SPI_MOSI_PIN, value);

    commandout <<= 1;
    CLOCK_STEP();
  }

  int adcout = 0;
  // read in one empty bit, one null bit and 10 ADC bits
  for (i=0; i<12; i++) {
    CLOCK_STEP();
    adcout <<= 1;
    adcout |= GPIO_INPUT_GET(SPI_MISO_PIN);
  }
  os_delay_us(CLOCK_DELAY);
  GPIO_OUTPUT_SET(SPI_CS_PIN, 1);

  adcout >>= 1; //      # first bit is 'null' so drop it

  return adcout;
}


