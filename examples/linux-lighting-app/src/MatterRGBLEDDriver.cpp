#include "MatterRGBLED.h"

#define MAX_LEDS 1024

MatterRGBLEDDriver::MatterRGBLEDDriver(const uint32_t &num_leds, const RGB_LED_ORDER_t &rgb_order)
    : _on_off_state{false}, _num_leds{num_leds}, _rgb_order{rgb_order}, _led_rgb_color{0}, _led_hsv_color{0}, _led_xy_color{0}, _led_temperature_color{0} {}

bool MatterRGBLEDDriver::GetOnOffState() const
{
    return _on_off_state;
}

int MatterRGBLEDDriver::Enable()
{
    if (GetOnOffState() == true)
    {
        return -1;
    }

    _on_off_state = true;
    return set_ws28xx_led_strip(_num_leds, _led_rgb_color.r, _led_rgb_color.g, _led_rgb_color.b, RGB_ORDER);
}

int MatterRGBLEDDriver::Disable()
{
    if (GetOnOffState() == false)
    {
        return -1;
    }

    _on_off_state = false;
    return set_ws28xx_led_strip(_num_leds, 0u, 0u, 0u, RGB_ORDER);
}

int MatterRGBLEDDriver::SetRGBLEDColor(const uint8_t &red, const uint8_t &green, const uint8_t &blue)
{
    _led_rgb_color =
    {
        .r = red,
        .g = green,
        .b = blue
    };

    if (GetOnOffState() == false)
    {
        return -1;
    }

    return set_ws28xx_led_strip(_num_leds, _led_rgb_color.r, _led_rgb_color.g, _led_rgb_color.b, RGB_ORDER);
}

int MatterRGBLEDDriver::SetHSVLEDColor(const uint8_t &hue, const uint8_t &saturation, const uint8_t &brightness)
{
    _led_hsv_color =
    {
        .h = hue, 
        .s = saturation,
        .v = brightness
    };

    RgbColor_t rgb = HsvToRgb(_led_hsv_color);

    return SetRGBLEDColor(rgb.r, rgb.g, rgb.b);
}

int MatterRGBLEDDriver::SetHLEDColor(const uint8_t &hue)
{
    _led_hsv_color.h = hue;
    RgbColor_t rgb = HsvToRgb(_led_hsv_color);

    return SetRGBLEDColor(rgb.r, rgb.g, rgb.b);
}

int MatterRGBLEDDriver::SetSLEDColor(const uint8_t &saturation)
{
    _led_hsv_color.s = saturation;
    RgbColor_t rgb = HsvToRgb(_led_hsv_color);

    return SetRGBLEDColor(rgb.r, rgb.g, rgb.b);
}

int MatterRGBLEDDriver::SetVLEDColor(const uint8_t &brightness)
{
    _led_hsv_color.v = brightness;
    RgbColor_t rgb = HsvToRgb(_led_hsv_color);

    return SetRGBLEDColor(rgb.r, rgb.g, rgb.b);
}

int MatterRGBLEDDriver::SetXYLEDColor(const uint16_t &currentX, const uint16_t &currentY)
{
    _led_xy_color =
    {
        .x = currentX,
        .y = currentY
    };

    RgbColor_t rgb = XYToRgb(_led_hsv_color.v, _led_xy_color.x, _led_xy_color.y);

    return SetRGBLEDColor(rgb.r, rgb.g, rgb.b);
}

int MatterRGBLEDDriver::SetXLEDColor(const uint16_t &currentX)
{
    _led_xy_color.x = currentX;
    RgbColor_t rgb = XYToRgb(_led_hsv_color.v, _led_xy_color.x, _led_xy_color.y);

    return SetRGBLEDColor(rgb.r, rgb.g, rgb.b);
}

int MatterRGBLEDDriver::SetYLEDColor(const uint16_t &currentY)
{
    _led_xy_color.y = currentY;
    RgbColor_t rgb = XYToRgb(_led_hsv_color.v, _led_xy_color.x, _led_xy_color.y);

    return SetRGBLEDColor(rgb.r, rgb.g, rgb.b);
}

int MatterRGBLEDDriver::SetTemperatureLEDColor(const uint16_t &temperature)
{
    _led_temperature_color =
    {
        .ctMireds = temperature
    };

    RgbColor_t rgb = CTToRgb(_led_temperature_color);

    return SetRGBLEDColor(rgb.r, rgb.g, rgb.b);
}
