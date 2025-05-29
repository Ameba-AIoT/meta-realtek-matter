#pragma once

#include "ws28xx_driver.h"
#include "ColorFormat.h"

class MatterRGBLEDDriver
{
public:
    MatterRGBLEDDriver(const uint32_t &num_leds = 1, const RGB_LED_ORDER_t &rgb_order = GRB);
    bool GetOnOffState() const;
    int Enable();
    int Disable();

    // Set RGB
    int SetRGBLEDColor(const uint8_t &red, const uint8_t &green, const uint8_t &blue);

    // Set HSV
    int SetHSVLEDColor(const uint8_t &hue, const uint8_t &saturation, const uint8_t &brightness);
    int SetHLEDColor(const uint8_t &hue);
    int SetSLEDColor(const uint8_t &saturation);
    int SetVLEDColor(const uint8_t &brightness);

    // Set XY
    int SetXYLEDColor(const uint16_t &currentX, const uint16_t &currentY);
    int SetXLEDColor(const uint16_t &currentX);
    int SetYLEDColor(const uint16_t &currentY);

    // Set Color Temperature
    int SetTemperatureLEDColor(const uint16_t &temperature);

private:
    bool _on_off_state;
    uint32_t _num_leds;
    RGB_LED_ORDER_t _rgb_order;
    RgbColor_t _led_rgb_color;
    HsvColor_t _led_hsv_color;
    XyColor_t _led_xy_color;
    CtColor_t _led_temperature_color;
};