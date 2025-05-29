SUMMARY = "Matter for Realtek Ameba"
DESCRIPTION = "Matter for Realtek Ameba"
SECTION = "meta-realtek-matter"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

# Choose the CHIP example apps you want to build. Refer to connectedhomeip/examples directory for possible options.
# Able to build multiple apps:
#    air-purifier-app \
#    air-quality-sensor-app \
#    all-clusters-app \ # Unable to run all-clusters-app, will get segmentation fault
#    all-clusters-minimal-app \ # Unable to run all-clusters-minimal-app, will get segmentation fault
#    bridge-app \
#    chef \ # Chef is not supported. Requires using chef.py to build.
#    contact-sensor-app \
#    dishwasher-app \
#    energy-management-app \
#    fabric-bridge-app \ # fabric-bridge-app is not available yet on v1.3-branch of connectedhomeip
#    lighting-app \
#    lit-icd-app \
#    lock-app \
#    log-source-app \ # log-source-app compile fails with error main.cpp:60:1: error: 'DiagnosticLogsCommandHandler' does not name a type
#    microwave-oven-app \
#    network-manager-app \
#    ota-provider-app \
#    ota-requestor-app \
#    persistent-storage \
#    refrigerator-app \
#    rvc-app \
#    thermostat \
#    tv-app \
#    tv-casting-app \
#

# The following matter apps are able to build, run, and commission:
#    air-purifier-app \
#    air-quality-sensor-app \
#    bridge-app \
#    contact-sensor-app \
#    dishwasher-app \
#    energy-management-app \
#    lighting-app \
#    lit-icd-app \
#    lock-app \
#    microwave-oven-app \
#    network-manager-app \
#    ota-provider-app \
#    ota-requestor-app \
#    persistent-storage \
#    refrigerator-app \
#    rvc-app \
#    thermostat \
#    tv-app \
#    tv-casting-app \
#
MATTER_APP_NAME ??= " \
    lighting-app \
    thermostat \
    "

# Specify path to the root directory of connectedhomeip repository
CHIP_ROOT ??= "${TOPDIR}/../../connectedhomeip"

# Specify the directory of Matter application source code. Matter_APP refers to individual elements inside MATTER_APP_NAME
MATTER_APP_SRC_DIR ??= "${CHIP_ROOT}/examples/${MATTER_APP}/linux"

# Specify the relative directory where the Matter application will be built, relative to MATTER_APP_SRC_DIR
MATTER_BUILD_DIR ??= "out/arm"

# Specify the directory where the Matter application will be installed on the target device
MATTER_APP_TARGET_DIR ??= "/matter-application"

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
