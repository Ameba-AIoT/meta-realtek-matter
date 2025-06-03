SUMMARY = "Matter Service"
DESCRIPTION = "Run Matter as service/daemon during startup"
SECTION = "meta-realtek-matter"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

inherit update-rc.d

INITSCRIPT_NAME = "matter-app"
INITSCRIPT_PARAMS = "start 99 3 5 . stop 10 0 1 6 ."

SRC_URI = "file://matter-app"

S = "${WORKDIR}"

do_install () {
    install -d ${D}/${sysconfdir}/init.d
    install -m 755 ${S}/matter-app ${D}/${sysconfdir}/init.d/matter-app
}

FILES:${PN} = "${sysconfdir}/init.d/matter-app"
