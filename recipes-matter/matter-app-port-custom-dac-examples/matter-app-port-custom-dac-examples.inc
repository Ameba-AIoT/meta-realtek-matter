SUMMARY = "Matter for Realtek Ameba"
DESCRIPTION = "Matter for Realtek Ameba"
SECTION = "meta-realtek-matter"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

MATTER_APP_NAME ??= " \
    linux-custom-dac-app \
    "

# Specify path to the root directory of connectedhomeip repository
CHIP_ROOT ??= "${TOPDIR}/../../connectedhomeip"

# Specify the directory of Matter application source code. Matter_APP refers to individual elements inside MATTER_APP_NAME
MATTER_APP_SRC_DIR ??= "${TOPDIR}/../sources/yocto/meta-realtek-matter/examples/${MATTER_APP}"

# Specify the relative directory where the Matter application will be built, relative to MATTER_APP_SRC_DIR
MATTER_BUILD_DIR ??= "out/arm"

# Specify the directory where the Matter application will be installed on the target device
MATTER_APP_TARGET_DIR ??= "/matter-app-port-examples"

# Specify CFLAGS to be passed
PLATFORM_CFLAGS .= '-DCHIP_DEVICE_CONFIG_WIFI_STATION_IF_NAME=\"wlan0\"", "'
PLATFORM_CFLAGS .= '-DCHIP_DEVICE_CONFIG_LINUX_DHCPC_CMD=\"udhcpc -b -i %s \"", "'

# Specify gn args to be passed to CHIP build. These will be placed inside --args as a string.
# Only lighting-app can import(\"//with_pw_rpc.gni\")
# treat_warnings_as_errors=false
MATTER_GN_ARGS ??= ' \
    is_debug=true \
    chip_enable_openthread=false \
    chip_enable_additional_data_advertising=true \
    chip_enable_rotating_device_id=true \
    target_cflags=[ "${PLATFORM_CFLAGS}" ] \
    '

# Specify gn gen arguments. These are arguments passed to gn gen.
MATTER_GN_GEN_ARGS ??= "--export-compile-commands"

# Specify build filename. By default, BUILD.gn should be at root of MATTER_APP_SRC_DIR
MATTER_BUILD_FILENAME ??= "BUILD.gn"
