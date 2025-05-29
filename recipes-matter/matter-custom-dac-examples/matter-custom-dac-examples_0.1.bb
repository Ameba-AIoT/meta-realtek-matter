require matter-custom-dac-examples.inc
inherit externalsrc

EXTERNALSRC_SYMLINKS = ""
EXTERNALSRC = "${CHIP_ROOT}"

DEPENDS += "glib-2.0-native dbus-glib-native gn-native ninja-native avahi pkgconfig-native python3-native python3-pip-native"
RDEPENDS:${PN} += "libgcc libstdc++ glibc glib-2.0 libavahi-client"

# If compile with args is_debug=true, remove FORTIFY_SOURCE=2
MATTER_GN_ARGS_IS_DEBUG_FLAG = "${@bb.utils.filter('MATTER_GN_ARGS', 'is_debug=true is_debug=false', d)}"
TARGET_CC_ARCH:remove = "${@oe.utils.conditional('MATTER_GN_ARGS_IS_DEBUG_FLAG','is_debug=false','','-D_FORTIFY_SOURCE=2',d)}"
# add -pg -finstrument-functions to TARGET_CC_ARCH if you want to use tracing tools
TARGET_CC_ARCH += "${LDFLAGS}"

# Matter compilation may require active internet connection to download some pip packages (e.g. using pigweed RPC)
do_configure[network] = "1"
do_compile[network] = "1"

# matter's sstate cache may not be in sync with actual connectedhomeip repository state, if you have manually deleted out directory. Enable to force do_configure to always run.
do_configure[nostamp] = "1"
do_compile[nostamp] = "1"

gn_gen () {
    for MATTER_APP in ${MATTER_APP_NAME}; do
        cd "${MATTER_APP_SRC_DIR}"
        gn gen ${MATTER_BUILD_DIR} ${MATTER_GN_GEN_ARGS} --args='
            target_os="linux"
            target_cpu="arm"
            arm_cpu="cortex-a32"
            arm_arch="armv8-a+crc"
            arm_fpu="neon"
            arm_float_abi="hard"
            custom_toolchain="${S}/build/toolchain/custom"
            target_cc="${CC}"
            target_cxx="${CXX}"
            target_ar="${AR}"
            ${MATTER_GN_ARGS}
            '
    done
}

do_configure () {
    cd ${S}
    . ${S}/scripts/activate.sh
   
   gn_gen
}

do_compile () {
    cd ${S}
    . ${S}/scripts/activate.sh
    
    for MATTER_APP in ${MATTER_APP_NAME}; do
        cd "${MATTER_APP_SRC_DIR}"
        ninja -C ${MATTER_BUILD_DIR}
    done
}

do_install () {
    install -d ${D}${MATTER_APP_TARGET_DIR}
    install -d ${D}${MATTER_APP_TARGET_DIR}/myattestation
    
    for MATTER_APP in ${MATTER_APP_NAME}; do
        cp -R --no-dereference --preserve=mode,links -v "${MATTER_APP_SRC_DIR}"/tools/factorydata/myattestation/* "${D}${MATTER_APP_TARGET_DIR}/myattestation"
        
        IS_MATTER_APP_INSTALLED=0
        
        if [ ! -f "${MATTER_APP_SRC_DIR}/${MATTER_BUILD_FILENAME}" ]; then
            bberror "For ${MATTER_APP}, cannot find ${MATTER_APP_SRC_DIR}/${MATTER_BUILD_FILENAME}"
            return 1
        fi
        
        # Extract strings of the executable names from BUILD.gn
        MATTER_EXECUTABLE_APP_NAME_LIST=$( \
        grep -o 'executable(.*)' "${MATTER_APP_SRC_DIR}/${MATTER_BUILD_FILENAME}" | \
        sed -n -e 's,executable(\(.*\)).*$,\1,p' | \
        cut -d \" -f 2 | \
        cut -d \' -f 2 | \
        cut -d \` -f 2)
        
        bbdebug 2 "MATTER_EXECUTABLE_APP_NAME_LIST=${MATTER_EXECUTABLE_APP_NAME_LIST}"
        
        OIFS=$IFS
        IFS=$'\n\r'
        # There may be multiple executables per MATTER_APP. Install executables if they exist
        for MATTER_EXECUTABLE_APP_NAME in ${MATTER_EXECUTABLE_APP_NAME_LIST}; do
            if [ ! -z "${MATTER_EXECUTABLE_APP_NAME}" ] && [ -f "${MATTER_APP_SRC_DIR}/${MATTER_BUILD_DIR}/${MATTER_EXECUTABLE_APP_NAME}" ]; then
                install -m 775 "${MATTER_APP_SRC_DIR}/${MATTER_BUILD_DIR}/${MATTER_EXECUTABLE_APP_NAME}" "${D}${MATTER_APP_TARGET_DIR}" && \
                IS_MATTER_APP_INSTALLED=1
                bbdebug 2 "Installed ${MATTER_APP} at target ${D}${MATTER_APP_TARGET_DIR}"
            else
                bbdebug 2 "For ${MATTER_APP}, Matter app executable \"${MATTER_EXECUTABLE_APP_NAME}\" was not found at ${MATTER_APP_SRC_DIR}/${MATTER_BUILD_DIR}/"
            fi
        done
        IFS=$OIFS

        if [ ${IS_MATTER_APP_INSTALLED} -eq 0 ]; then
            bbwarn "For ${MATTER_APP}, no Matter app executables were installed to target. \
            ${MATTER_BUILD_FILENAME} at ${MATTER_APP_SRC_DIR}/ must contain \"executable(...)\" function. \
            Check if executable exists at ${MATTER_APP_SRC_DIR}/${MATTER_BUILD_DIR}/"
        fi
    done
}

FILES:${PN} += "${MATTER_APP_TARGET_DIR} ${MATTER_APP_TARGET_DIR}/myattestation"
