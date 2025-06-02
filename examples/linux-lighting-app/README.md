# linux-lighting-app example

This is a modified example from [connectedhomeip/examples/lighting-app/linux](https://github.com/project-chip/connectedhomeip/tree/master/examples/lighting-app/linux).

This example demonstrates controlling LED brightness.

## Hardware setup

| Peripheral        | Pin   |
| ----------------- | ----- |
| LED               | PA_11 |
| WS2812B data line | PA_6  |

- Pin `PA_11` corresponds to pwmchip0 and pwm channel 3
- Only pin `PA_6` can be used for WS28XX RGB led

## DTS
- If not present, add the following to Device Tree Source (DTS) at `sources/kernel/linux-5.4/arch/arm/boot/dts/rtl8730elh-va*-generic.dts` (or `rtl8730elh-va*-full.dts`)

```bash
&timer8 {
	status = "okay";
};

&pwm {
	pinctrl-names = "default";
	pinctrl-0 = <&pwm_pins>;
	status = "okay";
};

&ledc{
	pinctrl-names = "default";
	pinctrl-0 = <&ledc_pins>;
	rtk,led-nums = <64>;
	rtk,output-RGB-mode = <0>; // Refer to spec for details
	rtk,data-tx-time0h = <0xC>;
	rtk,data-tx-time0l = <0x18>;
	rtk,data-tx-time1h = <0x18>;
	rtk,data-tx-time1l = <0x18>;
	rtk,refresh-time = <0x3FFF>;
	rtk,auto-dma-thred = <64>;
	dmas = <&dma 5>;
	dma-names = "dma_leds_tx";
	status = "okay";
};
```

- PWM uses timer8
- If using other RGB led other than WS2812, you may want to change the signal high and low timings (time0h, time0l, time1h, time1l, refresh-time) at the ledc section of the DTS
- Supported range of timings can usually be found in the datasheet of the RGB LED your are using
- The unit of time is 25ns
- Using `rtk,data-tx-time0h = <0xC>` as an example, `0xC` in decimal is `12`. So, `time0h` corresponds to `12 * 25ns = 300ns`

## Building
1. Ensure that `matter` is added to `DISTRO_FEATURES` at `${BUILDDIR}/conf/local.conf`
```bash
DISTRO_FEATURES:append = " matter "
```
- The path to `${BUILDDIR}` can be found by running the following command only after `source envsetup.sh` is run
```bash
echo ${BUILDDIR}
```

2. Edit the file `sources/yocto/meta-realtek-matter/recipes-matter/matter-app-port-examples/matter-app-port-examples.inc`, with the following
```bash
MATTER_APP_NAME ??= " \
    linux-lighting-app \
    "
```

3. Enable device drivers in menuconfig. Press `y` on keyboard to enable in menu.
```bash
bitbake virtual/kernel -c menuconfig
```

```bash
Device Drivers > Drivers for Realtek > PWM driver
```

```bash
Device Drivers > Drivers for Realtek > LED driver for WS28XXX
```

4. Follow [AmebaSmart Yocto Matter Guide](<../../doc/AmebaSmart Yocto Matter Guide.md>) for building, flashing, commissioning.

## Testing the example
We shall use chip-tool to control the led.

1. On target board, start the example
```bash
cd /matter-app-port-examples
./linux-lighting-app --wifi --discriminator 3840
```

2. On your host computer, commission matter app using `chip-tool`

Commission using ble-wifi
```bash
./chip-tool pairing ble-wifi 0x1234 "WIFI_SSID" "WIFI_PASSWORD" "20202021" "3840"
```

Alternatively, if the target board is already on same WIFI network as host machine, commission over network,
```bash
./chip-tool pairing onnetwork-long 0x1234 20202021 3840
```

You can check the current wireless WIFI settings on the target board as follows
```bash
# iwgetid
wlan0     ESSID:"WIFI_SSID"
```

Commissioning success console output from chip-tool:
```bash
...
CHIP:CTL: Commissioning complete for node ID 0x0000000000001234: success
CHIP:TOO: Device commissioning completed with success
...
```

3. Enable led
```bash
./chip-tool onoff on 0x1234 1
```

4. Increase led brightness
```bash
./chip-tool levelcontrol move-to-level 120 0 0 0 0x1234 1
```

5. Change RGB led colour
```bash
./chip-tool colorcontrol move-to-hue-and-saturation 200 160 0 0 0 0x1234 1
```

6. Disable led
```bash
./chip-tool onoff off 0x1234 1
```


## Create symlink
If the third_party or build_overrides symlink directories are not linking correctly due connectedhomeip not being on the same directory level as Yocto SDK, you may use the following as templates for how to create symlink to your connectedhomeip directory.

### Thirdparty folder softlink to matter

```bash
mkdir third_party
ln -s ../../../../../../../connectedhomeip third_party
```

### build_overrides folder softlink to matter

```bash
ln -s ../../../../../../connectedhomeip/examples/lighting-app/linux/build_overrides
```

