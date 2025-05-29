#pragma once

#include "MatterRGBLEDDriver.h"

// The maximum number of RGB LEDs that can be fully controlled depends on the SPI bus high and low timings
// So far, setting 337 RGB LEDs seems to be able to communicate with sysfs kernel. But, the absolute upper limit has not been tested.
// If you get Failed to write to hw_pattern: Invalid argument, try reducing the number of LEDs.
#define NUM_RGB_LEDS 64

// WS28XX RGB LED order
#define RGB_ORDER GRB

extern MatterRGBLEDDriver MatterRGBLED;