# linux-custom-dac-app example

This is a modified example from linux-lighting-app. You may consult linux-lighting-app example README.md first to get the hardware LED working.

This example demonstrates generation and use of test certificates and keys for matter commissioning.
In the main function, `DacFilepath` variable is where you can put in the filepath of the certificates and keys.
By default, the bitbake recipe shall copy the `myattestation` directory from `tools/factorydata` to the same folder as the executable binary `linux-custom-dac-app` at `/matter-app-port-examples` directory on target AmebaSmart Yocto.

## Generating test Certificates and Keys
1. Navigate to factorydata folder
```bash
cd tools/factorydata
```

2. Generate test certs and keys. 
Delete `myattestation` directory beforehand if you want to regenerate certificates and keys.
```bash
./gen-certs-enhanced.sh ~/dev/connectedhomeip ~/dev/connectedhomeip/out/host/chip-cert FFF1 8001
```

```bash
Is PAI vid-scoped (y/n)? y
How many DAC do you want to generate? 1
```

You should be able to see the generated certificates and keys
```bash
$ ls myattestation/*
myattestation/Chip-Test-CD-FFF1-8001.der
myattestation/Chip-Test-DAC-FFF1-8001-Cert-1.der
myattestation/Chip-Test-DAC-FFF1-8001-Cert-1.pem
myattestation/Chip-Test-DAC-FFF1-8001-Key-1.der
myattestation/Chip-Test-DAC-FFF1-8001-Key-1.pem
myattestation/Chip-Test-PAA-FFF1-Cert.der
myattestation/Chip-Test-PAA-FFF1-Cert.pem
myattestation/Chip-Test-PAA-FFF1-Key.der
myattestation/Chip-Test-PAA-FFF1-Key.pem
myattestation/Chip-Test-PAI-FFF1-8001-Cert.der
myattestation/Chip-Test-PAI-FFF1-8001-Cert.pem
myattestation/Chip-Test-PAI-FFF1-8001-Key.der
myattestation/Chip-Test-PAI-FFF1-8001-Key.pem
```

3. Generate private key file
For production matter device, you should be protecting your private key!
But in this example, for demonstration purposes, we shall simply create a private key file, that will be read and used during commissioning.

We use `gen-privkey-from-keypair.sh` script to help us to create a private key file.

First argument: Input `.der` filepath of the keypair. e.g. `myattestation/Chip-Test-DAC-FFF1-8001-Key-1.der`
Second argument: Output `.der` filepath of the private key. e.g. `myattestation/Chip-Test-DAC-FFF1-8001-PrivKey-1.der`

```bash
./gen-privkey-from-keypair.sh "myattestation/Chip-Test-DAC-FFF1-8001-Key-1.der" "myattestation/Chip-Test-DAC-FFF1-8001-PrivKey-1.der"
```

You should be able to see the private key file generated.
```bash
$ ls myattestation/*PrivKey
myattestation/Chip-Test-DAC-FFF1-8001-PrivKey-1.der
```

4. You have finished generating the test certificates and keys
`myattestation` directory will be copied over to the target board by bitbake recipe when you build and flash.


## Building
1. Ensure that `matter` is added to `DISTRO_FEATURES` at `${BUILDDIR}/conf/local.conf`
```bash
DISTRO_FEATURES:append = " matter "
```
- The path to `${BUILDDIR}` can be found by running the following command only after `source envsetup.sh` is run
```bash
echo ${BUILDDIR}
```

2. Follow [AmebaSmart Yocto Matter Guide](<../../doc/AmebaSmart Yocto Matter Guide.md>) for building, flashing, commissioning.

## Testing the example
We shall use chip-tool to commission.

1. On target board, start the example
```bash
cd /matter-app-port-examples
./linux-custom-dac-app --wifi --discriminator 3840
```

2. On your host computer, commission matter app using `chip-tool`

Commission using ble-wifi
```bash
./chip-tool pairing ble-wifi 0x1234 "WIFI_SSID" "WIFI_PASSWORD" "20202021" "3840" --paa-trust-store-path ~/dev/rtl8730e-linux-sdk/sources/yocto/meta-realtek-matter/examples/linux-custom-dac-app/tools/factorydata/myattestation
```

Alternatively, if the target board is already on same WIFI network as host machine, commission over network,
```bash
./chip-tool pairing onnetwork-long 0x1234 20202021 3840 --paa-trust-store-path ~/dev/rtl8730e-linux-sdk/sources/yocto/meta-realtek-matter/examples/linux-custom-dac-app/tools/factorydata/myattestation
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

