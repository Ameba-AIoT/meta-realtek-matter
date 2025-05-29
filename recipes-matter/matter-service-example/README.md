# matter-service example

This is an example script to demonstrate how to start Matter Application as a service/daemon

## Building
1. Add `matter-service-example` recipe to `RDEPENDS` at `sources/yocto/meta-realtek-matter/recipes-matter/packagegroups/packagegroup-matter-examples.bb`
```bash
RDEPENDS:${PN} = "\
...
    matter-service-example \
...
"
```

2. You may edit the file `sources/yocto/meta-realtek-matter/examples/matter-service/matter-app`, by changing the `DAEMON` to a compiled Matter Application example, e.g.:
```bash
DAEMON="/matter-app-port-examples/linux-lighting-app"
```

3. You may also edit the file `sources/yocto/meta-realtek-matter/examples/matter-service/matter-app`, by changing the `DAEMON_ARGS` that are passed to the `DAEMON`, e.g.:
```bash
DAEMON_ARGS="--wifi --vendor-id 0x8888 --product-id 0x9999 --passcode 27272727 --discriminator 3901"
```

4. Follow [AmebaSmart Yocto Matter Guide](<../../doc/AmebaSmart Yocto Matter Guide.md>) for building, flashing, commissioning.

## Testing the example
We shall use the example above, see the run-time changes, and commission using chip-tool.

1. On target board, boot the device, and wait until the Matter is executed:
```bash
Executing /matter-app-port-examples/linux-lighting-app
Matter Application started!
```

2. Matter Application will start and it will use the vendor-id, product-id, passcode, and discriminator passed in the matter-app:

```bash
CHIP:DL: Device Configuration:
CHIP:DL:   Serial Number: TEST_SN
CHIP:DL:   Vendor Id: 34952 (0x8888)
CHIP:DL:   Product Id: 39321 (0x9999)
CHIP:DL:   Product Name: TEST_PRODUCT
CHIP:DL:   Hardware Version: 0
CHIP:DL:   Setup Pin Code (0 for UNKNOWN/ERROR): 27272727
CHIP:DL:   Setup Discriminator (0xFFFF for UNKNOWN/ERROR): 3901 (0xF3D)
CHIP:DL:   Manufacturing Date: (not set)
CHIP:DL:   Device Type: 257 (0x101)
CHIP:-: ==== Onboarding payload for Standard Commissioning Flow ====
CHIP:SVR: SetupQRCode: [MT:OO-F6KUF15RS.E2YL00]
CHIP:SVR: Copy/paste the below URL in a browser to see the QR Code:
CHIP:SVR: https://project-chip.github.io/connectedhomeip/qrcode.html?data=MT%3AOO-F6KUF15RS.E2YL00
CHIP:SVR: Manual pairing code: [35890316647]
...
```

Matter Application log is also saved at /var/log/matter-app.log

3. On your host computer, commission matter app using `chip-tool`

Commission using ble-wifi
```bash
./chip-tool pairing ble-wifi 0x1234 "WIFI_SSID" "WIFI_PASSWORD" "27272727" "3901"
```

Alternatively, if the target board is already on same WIFI network as host machine, commission over network,
```bash
./chip-tool pairing onnetwork-long 0x1234 27272727 3901
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