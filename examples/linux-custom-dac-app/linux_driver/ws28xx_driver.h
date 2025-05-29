#ifndef _WS28XX_DRIVER_H
#define _WS28XX_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum RGB_LED_ORDER
{
    RGB,
    RBG,
    GRB,
    GBR,
    BRG,
    BGR
} RGB_LED_ORDER_t;

// Set all LEDs to the same color
int set_ws28xx_led_strip(uint32_t num_leds, uint8_t r, uint8_t g, uint8_t b, RGB_LED_ORDER_t rgb_order);

#ifdef __cplusplus
}
#endif

#endif