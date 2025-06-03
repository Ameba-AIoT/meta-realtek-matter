# Flashing to NAND for Yocto
After building the SDK, connect the board via USB and use Windows Image Tool to flash the image file.

Currently, only Windows Ameba Image Tool supports flashing to NAND flash, needed by AmebaSmart RTL8730E VA7 and VA8.

Flashing image involves three steps:
1. Connect with USB mode download
2. Copy Linux images from Ubuntu to Windows
3. Windows Image Tool

## Connect with USB mode download
1. Connect UART type-C port to provide 5V power
2. Connect micro B USB port
3. Trigger `Download` mode
	1. Hold Download button (UART_DOWNLOAD)
	2. Press and release reset EN pin (CHIP_EN)
	3. Release Download button

## Copy Linux images from Ubuntu to Windows
The Linux images built by Yocto can be found at `rtl8730e-linux-sdk/images/`.

Copy from Ubuntu to Windows the following:
1. `km4_boot_all.bin`
2. `km0_km4_app.bin`
3. `boot.img`
4. `xxx.dtb` ([Finding dtb filenames](<#finding-dtb-filenames>))
5. `kernel.img`
6. `rootfs.img`
7. `userdata.img`

- If using VMware Virtual Machine, [enable shared folder](https://docs.vmware.com/en/VMware-Workstation-Pro/17/com.vmware.ws.using.doc/GUID-D6D9A5FD-7F5F-4C95-AFAB-EDE9335F5562.html) to Windows host operating system to transfer files
    - VM -> Settings -> Options -> Shared Folders -> Check Always enabled -> Add host path to Windows Documents
    - In the following example, the linked folder name is set to Documents_ext
- Below shows example commands to copy images from Ubuntu (in VMware) to Windows folder `~/Documents/Realtek/Ameba/AmebaSmart/tools/ameba/binaries/va-x-xxx/`
    - va8-generic
	```bash
	IMG_DIRECTORY="${HOME}/dev/rtl8730e-linux-sdk/images/"
	IMG_DESTINATION="/mnt/hgfs/Documents_ext/Realtek/Ameba/AmebaSmart/tools/ameba/binaries/va-8-generic/"
	cp ${IMG_DIRECTORY}km4_boot_all.bin ${IMG_DESTINATION} && \
	cp ${IMG_DIRECTORY}km0_km4_app.bin ${IMG_DESTINATION} && \
	cp ${IMG_DIRECTORY}boot.img ${IMG_DESTINATION} && \
	cp ${IMG_DIRECTORY}rtl8730elh-va8-generic--5.4-r0-rtl8730elh-va8-20240629165442.dtb ${IMG_DESTINATION} && \
	cp ${IMG_DIRECTORY}kernel.img ${IMG_DESTINATION} && \
	cp ${IMG_DIRECTORY}rootfs.img ${IMG_DESTINATION} && \
	cp ${IMG_DIRECTORY}userdata.img ${IMG_DESTINATION}
	```
    - va8-full
	```bash
	IMG_DIRECTORY="${HOME}/dev/rtl8730e-linux-sdk/images/"
	IMG_DESTINATION="/mnt/hgfs/Documents_ext/Realtek/Ameba/AmebaSmart/tools/ameba/binaries/va-8-full"
	cp ${IMG_DIRECTORY}km4_boot_all.bin ${IMG_DESTINATION} && \
	cp ${IMG_DIRECTORY}km0_km4_app.bin ${IMG_DESTINATION} && \
	cp ${IMG_DIRECTORY}boot.img ${IMG_DESTINATION} && \
	cp ${IMG_DIRECTORY}rtl8730elh-va8-full--5.4-r0-rtl8730elh-va8-20240629171420.dtb ${IMG_DESTINATION} && \
	cp ${IMG_DIRECTORY}kernel.img ${IMG_DESTINATION} && \
	cp ${IMG_DIRECTORY}rootfs.img ${IMG_DESTINATION} && \
	cp ${IMG_DIRECTORY}userdata.img ${IMG_DESTINATION}
	```

### Finding dtb filenames
- At images directory, `~/rtl8730e-linux-sdk/images/`
- ameba-generic
	```bash
	find . -mindepth 1 ! -type l | grep ".dtb" | grep "generic"
	```
- ameba-full
	```bash
	find . -mindepth 1 ! -type l | grep ".dtb" | grep "full"
	```

## Windows Image Tool
1. Launch Windows Image Tool at `rtl8730e-linux-sdk/tools/ameba/ImageTool/AmebaImageTool.exe`
2. Open -> Device Profile. Device Profile can be found at `rtl8730e-linux-sdk/tools/ameba/DeviceProfiles/`
	- AmebaSmart-VA7: AmebaSmart_Linux_NAND_128MB_VA7.rdev
	- AmebaSmart-VA8: AmebaSmart_Linux_NAND_256MB_VA8.rdev
3.  Select respective `.bin` and `.img` that was built using Yocto
4.  Click Download
