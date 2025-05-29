# References
- AN0601_RTL8730E_Yocto_System_Application_Note_v2.9.pdf
# Yocto Setup for AmebaSmart
1. Install utility packages
	```bash
	sudo apt install -y chrpath diffstat liblz4-tool zstd gawk python3-pycryptodome repo
	```
2. Change shell to use bash
	```bash
	sudo dpkg-reconfigure dash
	```
	- Select `NO`
3. Create `/opt/rtk-toolchain/` directory
	```bash
	sudo mkdir -p /opt/rtk-toolchain
	sudo chown -R ${USER}:${USER} /opt/rtk-toolchain
	```
4. Get AmebaSmart Yocto SDK.
	```bash
	mkdir rtl8730e-linux-sdk-3.1-release
	cd rtl8730e-linux-sdk-3.1-release
	repo init -u https://github.com/Ameba-AIoT/ameba-linux-manifest -b ameba-3.1 -m ameba-3.1_r2.xml
	repo sync
	```

# Build AmebaSmart Yocto
> [!NOTE] 
> - First build will take a long time (~6hrs)
> - Requires internet connection to fetch source codes for packages
> - Subsequent builds will be faster as it can use local cache

1. Navigate inside `rtl8730e-linux-sdk-3.1-release`
	```bash
	cd rtl8730e-linux-sdk-3.1-release
	```
2. Run Yocto setup script
	```bash
	source envsetup.sh
	```
	- Choose AmebaSmart board: `rtl8730elh-va7` or `rtl8730elh-va8`
	- Choose distro: `ameba-generic` or `ameba-full`
3. Build all Linux images for target
	```bash
	m
	```
4. Build firmware boot and images
	- Generates `km4_boot_all.bin` and `km0_km4_app.bin`
	```bash
	mfw
	```
5. Built images can be found at `~/rtl8730e-linux-sdk-3.1-release/images/`
# Clean commands
## Clean build
```bash
m clean
```
## Clean firmware build
```bash
mfw clean
```

# Bitbake options
## kernel menuconfig
```bash
bitbake virtual/kernel -c menuconfig
```
## Save menuconfig
```bash
bitbake virtual/kernel -c savedefconfig
```
## BusyBox menuconfig
```bash
bitbake busybox -c menuconfig
```
## force compile
```bash
bitbake -c compile -f
```
## deploy
```bash
bitbake -c deploy
```
## cleanall
```bash
bitbake -c cleanall
```

# UART serial monitor
- Baudrate: `1500000`
- After flashing, reset the board by pressing `CHIP_EN` button

# SD card
## Location in Yocto
- SD card can be found at `/mnt/storage/`
