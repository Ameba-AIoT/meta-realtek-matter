require matter-app-examples.inc
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
    SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
    
    if [ ! -f "${S}/scripts/activate.sh" ]; then
        bbfatal "Could not find ${S}/scripts/activate.sh. Check that variable CHIP_ROOT at ${SCRIPT_DIR}/matter-app-examples.inc is correctly set."
        return 1
    fi

    if [ -z $(echo ${MATTER_APP_NAME} | xargs) ]; then
        bbnote "No Matter applications to generate."
        return 0
    fi

    cd ${S}
    . ${S}/scripts/activate.sh

    for MATTER_APP in ${MATTER_APP_NAME}; do

        if [ -d "${MATTER_APP_SRC_DIR}" ]; then
            cd "${MATTER_APP_SRC_DIR}"

            if [ ! -f "${MATTER_APP_SRC_DIR}/${MATTER_BUILD_FILENAME}" ]; then
                bberror "For ${MATTER_APP}, cannot find ${MATTER_APP_SRC_DIR}/${MATTER_BUILD_FILENAME}"
                return 1
            fi

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
            
            if [ $? -eq 0 ]; then
                bbnote "Successfully generated ninja build files for ${MATTER_APP}"
                continue
            else
                bbwarn "Failed to generate ninja build files for ${MATTER_APP}"
            fi

        else

            bberror "${MATTER_APP_SRC_DIR} does not exist."

        fi

        MATTER_APP_GEN_FAIL+="${MATTER_APP} "

    done

    if [ ! -z "${MATTER_APP_GEN_FAIL}" ]; then
        # Remove apps that failed to successfully generate ninja build files
        for MATTER_APP_TO_REMOVE in ${MATTER_APP_GEN_FAIL}; do
            MATTER_APP_NAME=$(echo "${MATTER_APP_NAME}" | sed 's/${MATTER_APP_TO_REMOVE}//g')
        done

        # Exit with error if all Matter applications failed to build
        if [ -z $(echo ${MATTER_APP_NAME} | xargs) ]; then
            bbfatal "All Matter applications failed to generate ninja build!"
            return 1
        fi
    else
        bbnote "All Matter applications successfully generated ninja build!"
    fi

    return 0
}

ninja_build () {
    SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
    
    if [ ! -f "${S}/scripts/activate.sh" ]; then
        bbfatal "Could not find ${S}/scripts/activate.sh. Check that variable CHIP_ROOT at ${SCRIPT_DIR}/matter-app-examples.inc is correctly set."
        return 1
    fi

    if [ -z $(echo ${MATTER_APP_NAME} | xargs) ]; then
        bbnote "No Matter applications to build."
        return 0
    fi

    cd ${S}
    . ${S}/scripts/activate.sh

    for MATTER_APP in ${MATTER_APP_NAME}; do

        if [ -d "${MATTER_APP_SRC_DIR}" ]; then
            cd "${MATTER_APP_SRC_DIR}"

            bbnote "Building Matter application: ${MATTER_APP} ..."

            ninja -C ${MATTER_BUILD_DIR}

            if [ $? -eq 0 ]; then
                bbnote "Successfully built ${MATTER_APP}"
                MATTER_APP_BUILD_SUCCESS+="${MATTER_APP} "
                continue
            else
                bbwarn "Failed to build ${MATTER_APP}"
            fi

        else

            bberror "${MATTER_APP_SRC_DIR} does not exist."

        fi

        MATTER_APP_BUILD_FAILED+="${MATTER_APP} "

    done

    # Print out summary of built results
    if [ ! -z "${MATTER_APP_BUILD_SUCCESS}" ]; then
        bbnote "Matter build success for:"
        for MATTER_APP in ${MATTER_APP_BUILD_SUCCESS}; do
            bbnote "    ${MATTER_APP}"
        done
    fi

    if [ ! -z "${MATTER_APP_BUILD_FAILED}" ]; then
        bbnote "Matter build failed for:"
        for MATTER_APP in ${MATTER_APP_BUILD_FAILED}; do
            bbnote "    ${MATTER_APP}"
        done

        return 1
    fi

    return 0
}

do_configure () {
    bbdebug 2 "S=${S}"
    bbdebug 2 "B=${B}"
    bbdebug 2 "D=${D}"

    gn_gen

    bbdebug 2 "Finished Matter do_configure: ${MATTER_APP_NAME}"
}

do_compile () {
    bbdebug 2 "---------- Compile Variables ----------"
    bbdebug 2 "SELECTED_OPTIMIZATION=${SELECTED_OPTIMIZATION}"
    bbdebug 2 "LDFLAGS=${LDFLAGS}"
    bbdebug 2 "TARGET_CC_ARCH=${TARGET_CC_ARCH}"
    bbdebug 2 "CFLAGS=${CFLAGS}"
    bbdebug 2 "TARGET_CFLAGS=${TARGET_CFLAGS}"
    bbdebug 2 "CXXFLAGS=${CXXFLAGS}"
    bbdebug 2 "TARGET_CXXFLAGS=${TARGET_CXXFLAGS}"
    bbdebug 2 "CC=${CC}"
    bbdebug 2 "CXX=${CXX}"
    bbdebug 2 "---------- Compile Variables END ----------"

    ninja_build
}

do_install () {
    install -d ${D}${MATTER_APP_TARGET_DIR}
    
    for MATTER_APP in ${MATTER_APP_NAME}; do

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

FILES:${PN} += "${MATTER_APP_TARGET_DIR}"
