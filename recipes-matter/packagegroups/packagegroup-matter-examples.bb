SUMMARY = "Matter for Realtek Ameba"
DESCRIPTION = "Matter for Realtek Ameba"
SECTION = "meta-realtek-matter"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit packagegroup

RDEPENDS:${PN} = "\
    matter-non-ported-examples \
    matter-ported-examples \
    matter-custom-dac-examples \
"
