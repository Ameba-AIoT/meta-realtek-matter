#include "ws28xx_driver.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define HW_PATTERN_PATH "/sys/devices/platform/ocp/41008000.led-controller/leds/rtk_ws28xxx:common/hw_pattern"

static int set_ws28xx_hw_pattern(const char *buf, const size_t len) {
    int fd;

    if ((fd = open(HW_PATTERN_PATH, O_WRONLY)) < 0)
    {
        int errsv = errno;
        fprintf(stderr, "Failed to open hw_pattern: %s\n", strerror(errsv));
        return errsv;
    }

    printf("Writing to hw_pattern, buf = %s\n", buf);

    if (write(fd, buf, len) < 0) {
        int errsv = errno;
        close(fd);
        fprintf(stderr, "Failed to write to hw_pattern: %s\n", strerror(errsv));
        return errsv;
    }

    if (close(fd) < 0)
    {
        int errsv = errno;
        fprintf(stderr, "Failed to close hw_pattern: %s\n", strerror(errsv));
        return errsv;
    }

    return 0;
}

static uint32_t get_formatted_color(const uint8_t r, const uint8_t g, const uint8_t b, const RGB_LED_ORDER_t rgb_order)
{
    switch (rgb_order)
    {
        case RGB:
            return (r << 16) | (g << 8) | b;
        case RBG:
            return (r << 16) | (b << 8) | g;
        case GRB:
            return (g << 16) | (r << 8) | b;
        case GBR:
            return (g << 16) | (b << 8) | r;
        case BRG:
            return (b << 16) | (r << 8) | g;
        case BGR:
            return (b << 16) | (g << 8) | r;
        default:
            return 0;
    }
}

// Set all LEDs to the same color
int set_ws28xx_led_strip(const uint32_t num_leds, const uint8_t r, const uint8_t g, const uint8_t b, const RGB_LED_ORDER_t rgb_order)
{
    if (num_leds < 1)
    {
        fprintf(stderr, "Invalid number of LEDs. Choose at least 1 LEDs.\n");
        return -1;
    }

    const uint32_t color = get_formatted_color(r, g, b, rgb_order);
    const int len = snprintf(NULL, 0, " %u %u", color, 0u);

    if (len < 0)
    {
        fprintf(stderr, "Failed to calculate length of needed buf\n");
        return -1;
    }

    const size_t color_size = (size_t) len;

    const size_t buf_size = num_leds * color_size + 1;

    char *buf = (char *) calloc(buf_size, sizeof(char));

    if (buf == NULL)
    {
        fprintf(stderr, "Failed to allocate %zu bytes of memory for buf\n", buf_size);
        return -1;
    }
    int pos = 0;

    for (uint32_t i = 0; i < num_leds; i++)
    {
        pos += snprintf(&buf[pos], color_size + 1, " %u %u", color, 0u);
        if (pos >= (int) buf_size)
        {
            fprintf(stderr, "buf overflow. pos=%d\n", pos);
            return -1;
        }

        if (pos < 0)
        {
            fprintf(stderr, "Failed to write to buf\n");
            return -1;
        }
    }

    int ret = set_ws28xx_hw_pattern(buf, (size_t) pos + 1);

    free(buf);

    return ret;
}