## TMPDIR has changed location. You need to either move it back
- Fix: edit `~/rtl8730e-linux-sdk/build_rtl8730elh-va8-full/tmp/saved_tmpdir`
## Recipe kmod-crypto sets B variable with trailing slash
- At `~/rtl8730e-linux-sdk/sources/yocto/meta-realtek/meta-realtek-bsp/recipes-test/kmod-crypto/kmod-crypto_1.0.bb`
- Remove the trailing slash for `EXTERNALSRC`
```bash
EXTERNALSRC = "${RTKDIR}/tests/crypto"
```
## Recipe kmod-timer sets B variable with trailing slash
- At `~/rtl8730e-linux-sdk/sources/yocto/meta-realtek/meta-realtek-bsp/recipes-test/kmod-timer/kmod-timer_1.0.bb`
- Remove the trailing slash for `EXTERNALSRC`
```bash
EXTERNALSRC = "${RTKDIR}/tests/timer_hw"
```

## Recipe inherits features_check but doesn't use it
- At `~/rtl8730e-linux-sdk/sources/yocto/meta-realtek/meta-realtek-bsp/recipes-graphics/lvgl/lv-drivers_7.11.0.bb`
- Comment out `inherit features_check`
```
# inherit features_check
```

## ERROR: optee-os-ameba-3.13.0-r0 do_compile: ExecutionError

> [!CAUTION] 
> ModuleNotFoundError: No module named 'Cryptodome'

<details>
  <summary>example output</summary>

```bash
NOTE: optee-os-ameba: compiling from external source tree /home/zivlow/dev/rtl8730e-linux-sdk/sources/boot/optee/optee_os
ERROR: optee-os-ameba-3.13.0-r0 do_compile: oe_runmake failed
ERROR: optee-os-ameba-3.13.0-r0 do_compile: ExecutionError('/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/temp/run.do_compile.2647954', 1, None, None)
ERROR: Logfile of failure stored in: /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/temp/log.do_compile.2647954
Log data follows:
| DEBUG: Executing python function externalsrc_compile_prefunc
| NOTE: optee-os-ameba: compiling from external source tree /home/zivlow/dev/rtl8730e-linux-sdk/sources/boot/optee/optee_os
| DEBUG: Python function externalsrc_compile_prefunc finished
| DEBUG: Executing python function autotools_aclocals
| DEBUG: SITE files ['endian-little', 'bit-32', 'arm-common', 'arm-32', 'common-linux', 'common-glibc', 'arm-linux', 'arm-linux-gnueabi', 'common']
| DEBUG: Python function autotools_aclocals finished
| DEBUG: Executing shell function do_compile
| NOTE: make -j 8 -C /home/zivlow/dev/rtl8730e-linux-sdk/sources/boot/optee/optee_os O=/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0 V=1 PLATFORM=realtek CFG_TEE_TA_LOG_LEVEL=1 CFG_TEE_CORE_LOG_LEVEL=1 CROSS_COMPILE=arm-rtk-linux-gnueabi- CROSS_COMPILE_core=arm-rtk-linux-gnueabi- CROSS_COMPILE_ta_arm64= CFG_TEE_BENCHMARK=n all
| make: Entering directory '/home/zivlow/dev/rtl8730e-linux-sdk/sources/boot/optee/optee_os'
| set -e; true '  CHK     /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/conf.mk'; cnf='CFG_8250_UART=y_nl_ CFG_AES_GCM_TABLE_BASED=y_nl_ CFG_ARM32_core=y_nl_ CFG_ARM32_ldelf=y_nl_ CFG_ARM32_ta_arm32=y_nl_ CFG_ARM64_core=n_nl_ CFG_BOOT_SECONDARY_REQUEST=y_nl_ CFG_CC_OPT_LEVEL=s_nl_ CFG_COMPAT_GP10_DES=y_nl_ CFG_CORE_ASLR=y_nl_ CFG_CORE_BGET_BESTFIT=n_nl_ CFG_CORE_BIGNUM_MAX_BITS=4096_nl_ CFG_CORE_CLUSTER_SHIFT=2_nl_ CFG_CORE_DEBUG_CHECK_STACKS=n_nl_ CFG_CORE_DUMP_OOM=n_nl_ CFG_CORE_DYN_SHM=y_nl_ CFG_CORE_HEAP_SIZE=65536_nl_ CFG_CORE_HUK_SUBKEY_COMPAT=y_nl_ CFG_CORE_LARGE_PHYS_ADDR=n_nl_ CFG_CORE_MAX_SYSCALL_RECURSION=4_nl_ CFG_CORE_MBEDTLS_MPI=y_nl_ CFG_CORE_NEX_HEAP_SIZE=16384_nl_ CFG_CORE_PAGE_TAG_AND_IV=n_nl_ CFG_CORE_RESERVED_SHM=y_nl_ CFG_CORE_RODATA_NOEXEC=n_nl_ CFG_CORE_RWDATA_NOEXEC=y_nl_ CFG_CORE_SANITIZE_KADDRESS=n_nl_ CFG_CORE_SANITIZE_UNDEFINED=n_nl_ CFG_CORE_THREAD_SHIFT=0_nl_ CFG_CORE_TPM_EVENT_LOG=n_nl_ CFG_CORE_TZSRAM_EMUL_SIZE=458752_nl_ CFG_CORE_UNMAP_CORE_AT_EL0=y_nl_ CFG_CORE_WORKAROUND_NSITR_CACHE_PRIME=y_nl_ CFG_CORE_WORKAROUND_SPECTRE_BP=y_nl_ CFG_CORE_WORKAROUND_SPECTRE_BP_SEC=y_nl_ CFG_CRYPTO=y_nl_ CFG_CRYPTOLIB_DIR=core/lib/libtomcrypt_nl_ CFG_CRYPTOLIB_NAME=tomcrypt_nl_ CFG_CRYPTOLIB_NAME_tomcrypt=y_nl_ CFG_CRYPTO_AES=y_nl_ CFG_CRYPTO_AES_GCM_FROM_CRYPTOLIB=n_nl_ CFG_CRYPTO_CBC=y_nl_ CFG_CRYPTO_CBC_MAC=y_nl_ CFG_CRYPTO_CCM=y_nl_ CFG_CRYPTO_CMAC=y_nl_ CFG_CRYPTO_CONCAT_KDF=y_nl_ CFG_CRYPTO_CTR=y_nl_ CFG_CRYPTO_CTS=y_nl_ CFG_CRYPTO_DES=y_nl_ CFG_CRYPTO_DH=y_nl_ CFG_CRYPTO_DSA=y_nl_ CFG_CRYPTO_ECB=y_nl_ CFG_CRYPTO_ECC=y_nl_ CFG_CRYPTO_GCM=y_nl_ CFG_CRYPTO_HKDF=y_nl_ CFG_CRYPTO_HMAC=y_nl_ CFG_CRYPTO_MD5=y_nl_ CFG_CRYPTO_PBKDF2=y_nl_ CFG_CRYPTO_RSA=y_nl_ CFG_CRYPTO_RSASSA_NA1=y_nl_ CFG_CRYPTO_SHA1=y_nl_ CFG_CRYPTO_SHA224=y_nl_ CFG_CRYPTO_SHA256=y_nl_ CFG_CRYPTO_SHA384=y_nl_ CFG_CRYPTO_SHA512=y_nl_ CFG_CRYPTO_SHA512_256=y_nl_ CFG_CRYPTO_SIZE_OPTIMIZATION=y_nl_ CFG_CRYPTO_SM2_DSA=y_nl_ CFG_CRYPTO_SM2_KEP=y_nl_ CFG_CRYPTO_SM2_PKE=y_nl_ CFG_CRYPTO_SM3=y_nl_ CFG_CRYPTO_SM4=y_nl_ CFG_CRYPTO_XTS=y_nl_ CFG_DEBUG_INFO=y_nl_ CFG_DEVICE_ENUM_PTA=y_nl_ CFG_DT=n_nl_ CFG_DTB_MAX_SIZE=0x10000_nl_ CFG_EARLY_TA=n_nl_ CFG_EARLY_TA_COMPRESS=y_nl_ CFG_EMBED_DTB=n_nl_ CFG_ENABLE_EMBEDDED_TESTS=n_nl_ CFG_ENABLE_SCTLR_Z=n_nl_ CFG_EXTERNAL_DTB_OVERLAY=n_nl_ CFG_FTRACE_BUF_WHEN_FULL=shift_nl_ CFG_FTRACE_SUPPORT=n_nl_ CFG_FTRACE_US_MS=10000_nl_ CFG_GENERIC_BOOT=y_nl_ CFG_GIC=y_nl_ CFG_GP_SOCKETS=y_nl_ CFG_HWSUPP_MEM_PERM_PXN=y_nl_ CFG_HWSUPP_MEM_PERM_WXN=y_nl_ CFG_INIT_CNTVOFF=y_nl_ CFG_KERN_LINKER_ARCH=arm_nl_ CFG_KERN_LINKER_FORMAT=elf32-littlearm_nl_ CFG_LIBUTILS_WITH_ISOC=y_nl_ CFG_LOCKDEP=n_nl_ CFG_LOCKDEP_RECORD_STACK=y_nl_ CFG_LPAE_ADDR_SPACE_BITS=32_nl_ CFG_MMAP_REGIONS=20_nl_ CFG_MSG_LONG_PREFIX_MASK=0x1a_nl_ CFG_NUM_THREADS=2_nl_ CFG_OPTEE_REVISION_MAJOR=3_nl_ CFG_OPTEE_REVISION_MINOR=13_nl_ CFG_OS_REV_REPORTS_GIT_SHA1=y_nl_ CFG_PAGED_USER_TA=n_nl_ CFG_PKCS11_TA_ALLOW_DIGEST_KEY=y_nl_ CFG_PKCS11_TA_AUTH_TEE_IDENTITY=y_nl_ CFG_PM_ARM32=y_nl_ CFG_PM_STUBS=y_nl_ CFG_PSCI_ARM32=y_nl_ CFG_REE_FS=y_nl_ CFG_REE_FS_TA=y_nl_ CFG_REE_FS_TA_BUFFERED=n_nl_ CFG_RESERVED_VASPACE_SIZE=(1024 * 1024 * 10)_nl_ CFG_RPMB_FS=n_nl_ CFG_RPMB_FS_CACHE_ENTRIES=0_nl_ CFG_RPMB_FS_DEV_ID=0_nl_ CFG_RPMB_FS_RD_ENTRIES=8_nl_ CFG_RPMB_WRITE_KEY=n_nl_ CFG_SCMI_MSG_CLOCK=n_nl_ CFG_SCMI_MSG_DRIVERS=n_nl_ CFG_SCMI_MSG_RESET_DOMAIN=n_nl_ CFG_SCMI_MSG_SMT=n_nl_ CFG_SCMI_MSG_VOLTAGE_DOMAIN=n_nl_ CFG_SCMI_PTA=n_nl_ CFG_SCTLR_ALIGNMENT_CHECK=n_nl_ CFG_SECSTOR_TA=y_nl_ CFG_SECSTOR_TA_MGMT_PTA=y_nl_ CFG_SECURE_DATA_PATH=n_nl_ CFG_SECURE_PARTITION=n_nl_ CFG_SECURE_TIME_SOURCE_CNTPCT=y_nl_ CFG_SHMEM_SIZE=0x00020000_nl_ CFG_SHMEM_START=0x602e0000_nl_ CFG_SHOW_CONF_ON_BOOT=n_nl_ CFG_SM_NO_CYCLE_COUNTING=y_nl_ CFG_STACK_THREAD_EXTRA=0_nl_ CFG_STACK_TMP_EXTRA=0_nl_ CFG_SYSCALL_FTRACE=n_nl_ CFG_SYSCALL_WRAPPERS_MCOUNT=n_nl_ CFG_SYSTEM_PTA=y_nl_ CFG_TA_ASLR=y_nl_ CFG_TA_ASLR_MAX_OFFSET_PAGES=128_nl_ CFG_TA_ASLR_MIN_OFFSET_PAGES=0_nl_ CFG_TA_BGET_TEST=n_nl_ CFG_TA_BIGNUM_MAX_BITS=2048_nl_ CFG_TA_DYNLINK=y_nl_ CFG_TA_FLOAT_SUPPORT=y_nl_ CFG_TA_GPROF_SUPPORT=n_nl_ CFG_TA_MBEDTLS=y_nl_ CFG_TA_MBEDTLS_MPI=y_nl_ CFG_TA_MBEDTLS_SELF_TEST=y_nl_ CFG_TA_STRICT_ANNOTATION_CHECKS=y_nl_ CFG_TEE_API_VERSION=GPD-1.1-dev_nl_ CFG_TEE_BENCHMARK=n_nl_ CFG_TEE_CORE_DEBUG=y_nl_ CFG_TEE_CORE_EMBED_INTERNAL_TESTS=n_nl_ CFG_TEE_CORE_LOG_LEVEL=1_nl_ CFG_TEE_CORE_MALLOC_DEBUG=n_nl_ CFG_TEE_CORE_NB_CORE=2_nl_ CFG_TEE_CORE_TA_TRACE=y_nl_ CFG_TEE_FW_IMPL_VERSION=FW_IMPL_UNDEF_nl_ CFG_TEE_FW_MANUFACTURER=FW_MAN_UNDEF_nl_ CFG_TEE_IMPL_DESCR=OPTEE_nl_ CFG_TEE_MANUFACTURER=LINARO_nl_ CFG_TEE_RAM_VA_SIZE=0x000A0000_nl_ CFG_TEE_TA_LOG_LEVEL=1_nl_ CFG_TEE_TA_MALLOC_DEBUG=n_nl_ CFG_TZDRAM_SIZE=0x000e0000_nl_ CFG_TZDRAM_START=0x70200000_nl_ CFG_ULIBS_MCOUNT=n_nl_ CFG_ULIBS_SHARED=n_nl_ CFG_UNWIND=y_nl_ CFG_USER_TA_TARGETS=ta_arm32_nl_ CFG_VIRTUALIZATION=n_nl_ CFG_WITH_PAGER=n_nl_ CFG_WITH_SOFTWARE_PRNG=y_nl_ CFG_WITH_STACK_CANARIES=y_nl_ CFG_WITH_STATS=y_nl_ CFG_WITH_STMM_SP=n_nl_ CFG_WITH_USER_TA=y_nl_ CFG_WITH_VFP=y_nl_'; mkdir -p /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/; echo "# auto-generated TEE configuration file" >/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/conf.mk.tmp; echo "# TEE version ce3edc458-dev" >>/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/conf.mk.tmp; echo "ARCH=arm" >>/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/conf.mk.tmp; echo "PLATFORM=realtek" >>/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/conf.mk.tmp; echo "PLATFORM_FLAVOR=amebasmart_armv7a" >>/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/conf.mk.tmp; echo -n "${cnf}" | sed 's/_nl_ */\n/g' >>/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/conf.mk.tmp; 	if cmp -s /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/conf.mk /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/conf.mk.tmp; then rm -f /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/conf.mk.tmp; else true '  UPD     /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/conf.mk'; mv /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/conf.mk.tmp /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/conf.mk; fi
| mkdir -p /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/core
| python3 scripts/pem_to_pub_c.py --prefix ta_pub_key --key keys/default_ta.pem --out /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/core/ta_pub_key.c
| Traceback (most recent call last):
|   File "/home/zivlow/dev/rtl8730e-linux-sdk/sources/boot/optee/optee_os/scripts/pem_to_pub_c.py", line 25, in main
|     from Cryptodome.PublicKey import RSA
| ModuleNotFoundError: No module named 'Cryptodome'
| 
| During handling of the above exception, another exception occurred:
| 
| Traceback (most recent call last):
|   File "/home/zivlow/dev/rtl8730e-linux-sdk/sources/boot/optee/optee_os/scripts/pem_to_pub_c.py", line 65, in module
|     main()
|   File "/home/zivlow/dev/rtl8730e-linux-sdk/sources/boot/optee/optee_os/scripts/pem_to_pub_c.py", line 28, in main
|     from Crypto.PublicKey import RSA
| ModuleNotFoundError: No module named 'Crypto'
| make: *** [mk/subdir.mk:181: /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/optee-os-ameba-3.13.0/core/ta_pub_key.c] Error 1
| make: *** Waiting for unfinished jobs....
| make: Leaving directory '/home/zivlow/dev/rtl8730e-linux-sdk/sources/boot/optee/optee_os'
| ERROR: oe_runmake failed
| WARNING: /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/temp/run.do_compile.2647954:179 exit 1 from 'exit 1'
| WARNING: Backtrace (BB generated script):
| 	#1: bbfatal_log, /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/temp/run.do_compile.2647954, line 179
| 	#2: die, /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/temp/run.do_compile.2647954, line 163
| 	#3: oe_runmake, /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/temp/run.do_compile.2647954, line 158
| 	#4: do_compile, /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/temp/run.do_compile.2647954, line 153
| 	#5: main, /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/rtl8730elh_va8-rtk-linux-gnueabi/optee-os-ameba/3.13.0-r0/temp/run.do_compile.2647954, line 192
ERROR: Task (/home/zivlow/dev/rtl8730e-linux-sdk/sources/yocto/poky/../meta-realtek/meta-realtek-bsp/recipes-security/optee/optee-os-ameba_3.13.0.bb:do_compile) failed with exit code '1'
```

</details>

- Fix: install `python3-pycryptodome`
```bash
sudo apt install python3-pycryptodome
```

Alternatively,
> [!TIP] 
> Install pycryptodomex in system Python pip, not in your own virtual environment

```bash
python3 -m pip install pycryptodomex
```

> [!TIP] 
> If pycryptodomex did not work, may also try to install pycryptodome

```bash
python3 -m pip install pycryptodome
```
## WARNING: Unable to get checksum for linux-ameba SRC_URI entry bsp

> [!WARNING] 
> No fix found yet
> - This is non-fatal warning
<details>
  <summary>example output</summary>
  
  ```bash
  WARNING: Unable to get checksum for linux-ameba SRC_URI entry bsp: [Errno 2] No such file or directory: '/home/zivlow/rtl8730e-linux-sdk/sources/kernel/linux-5.4/arch/riscv/bsp'
  WARNING: Unable to get checksum for linux-ameba SRC_URI entry bsp: [Errno 2] No such file or directory: '/home/zivlow/rtl8730e-linux-sdk/sources/kernel/linux-5.4/arch/arm64/bsp'
  WARNING: Unable to get checksum for linux-ameba SRC_URI entry bsp: [Errno 2] No such file or directory: '/home/zivlow/rtl8730e-linux-sdk/sources/kernel/linux-5.4/arch/arm/bsp'
  WARNING: Unable to get checksum for linux-ameba SRC_URI entry bsp: [Errno 2] No such file or directory: '/home/zivlow/rtl8730e-linux-sdk/sources/kernel/linux-5.4/arch/mips/bsp'
  ```
  
</details>

## WARNING: Unable to get checksum for linux-ameba SRC_URI entry vexpress-v2m-rs1.dtsi
> [!WARNING] 
> No fix found yet
> - This is non-fatal warning

<details>
  <summary>example output</summary>

  ```bash
  WARNING: Unable to get checksum for linux-ameba SRC_URI entry vexpress-v2m-rs1.dtsi: [Errno 2] No such file or directory: '/home/zivlow/rtl8730e-linux-sdk/sources/kernel/linux-5.4/arch/arm64/boot/dts/arm/vexpress-v2m-rs1.dtsi'
  ```
  
</details>

## /usr/lib/libstdc++.so.6: version `GLIBCXX_3.4.30' not found
- This error occurs when cross-compiling, the host machine is using a newer version of `libstdc++` to perform cross-compilation

> [!TIP] 
> Link 'libstdc++.so.6' to an older version like 'libstdc++.so.6.0.29'

- Check your GLIBCXX supported versions
```bash
strings /usr/lib/libstdc++.so.6 | grep GLIBCXX
```
- May be inside `/usr/lib/gcc-cross/arm-linux-gnueabihf/11/` directory instead for your system.
```bash
strings /usr/lib/gcc-cross/arm-linux-gnueabihf/11/libstdc++.so | grep GLIBCXX
```
- Check your GLIBCXX supported versions (arm)
```bash
strings /usr/arm-linux-gnueabihf/lib/libstdc++.so.6 | grep GLIBCXX
```

- Copy the older C++ library from AmebaSmart Yocto
```bash
cp /usr/lib/libstdc++.so.6.0.29 /mnt/storage/mmcblk0p2
```

- Link `libstdc++.so.6` library to older C++ library
```bash
cd /usr/arm-linux-gnueabihf/lib
sudo ln -sf libstdc++.so.6.0.29 libstdc++.so.6 
```

- Verify symlink
```bash
cd /usr/arm-linux-gnueabihf/lib
ls -al | grep libstdc++
```

## do_package_qa: QA Issue: File xxx doesn't have GNU_HASH (didn't pass LDFLAGS?)
### Fix by ignoring QA check
- Suitable for pre-compiled binaries
- Add the following skip near the end of your recipe
```bash
INSANE_SKIP:${PN} += "ldflags"
```
### Fix by including LDFLAGS during compilation
- Add the following before compilation of binary
```bash
TARGET_CC_ARCH += "${LDFLAGS}"
```

## EXTERNALSRC must be an absolute path
- This error occurs when trying to build Yocto eSDK script with `bitbake ameba-image-core -c populate_sdk_ext`
- This error occurs because in `ameba-sdk`, there are many uses of `externalsrc` which has variables pointing to `${RTKDIR}/...`
	- The `externalsrc.bbclass` performs a simple check for absolute path such that it starts with the root directory `/`, but in `ameba-sdk`, externalsrc variables starts with `$`, and `${RTKDIR}` variable expansion has not occurred yet
- At `~/rtl8730e-linux-sdk/sources/yocto/poky/meta/classes/externalsrc.bbclass`
- Comment out the following path checks
```python
    #if externalsrc and not externalsrc.startswith("/"):
    #    bb.error("EXTERNALSRC must be an absolute path")
    #if externalsrcbuild and not externalsrcbuild.startswith("/"):
    #    bb.error("EXTERNALSRC_BUILD must be an absolute path")
```

# New recipe not compiling
- Recipes will not run, unless they are included in `IMAGE_INSTALL` variable
- At `conf/layer.conf` of the layer, make sure your recipe name is added to the `IMAGE_INSTALL` variable
```bash
IMAGE_INSTALL += "your-new-recipe"
```

# openssl-3.0.7-r0 do_package_write_ipk: Fatal errors occurred in subprocesses
- This error may occur during first fresh run using `m` or when `sstate_cache` is deleted
- You may get `non-zero exit status 137`, indicating OOM, and  `Broken pipe` error message on console as follows:

<details>
  <summary>example output</summary>

```bash
ERROR: openssl-3.0.7-r0 do_package_write_ipk: Fatal errors occurred in subprocesses:
Command 'PATH="/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/sysroots-uninative/x86_64-linux/usr/bin:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/recipe-sysroot-native/usr/bin/perl-native:/home/zivlow/dev/rtl8730e-linux-sdk/sources/yocto/poky/scripts:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/recipe-sysroot-native/usr/bin/arm-rtk-linux-gnueabi:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/recipe-sysroot/usr/bin/crossscripts:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/recipe-sysroot-native/usr/sbin:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/recipe-sysroot-native/usr/bin:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/recipe-sysroot-native/sbin:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/recipe-sysroot-native/bin:/home/zivlow/dev/rtl8730e-linux-sdk/sources/yocto/poky/bitbake/bin:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/hosttools" opkg-build -Z xz -a "--memlimit=50% --threads=8" openssl-dbg /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/deploy-ipks/cortexa32hf-neon' returned non-zero exit status 137.
Subprocess output:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/recipe-sysroot-native/usr/bin/opkg-build: line 317: 2282216 Broken pipe             tar $ogargs $tsortargs --no-recursion $mtime_args -c $tarformat -T $tmp_dir/file_list
     2282217 Killed                  | $compressor $compressorargs > $tmp_dir/data.tar.$cext
Command 'PATH="/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/sysroots-uninative/x86_64-linux/usr/bin:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/recipe-sysroot-native/usr/bin/perl-native:/home/zivlow/dev/rtl8730e-linux-sdk/sources/yocto/poky/scripts:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/recipe-sysroot-native/usr/bin/arm-rtk-linux-gnueabi:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/recipe-sysroot/usr/bin/crossscripts:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/recipe-sysroot-native/usr/sbin:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/recipe-sysroot-native/usr/bin:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/recipe-sysroot-native/sbin:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/recipe-sysroot-native/bin:/home/zivlow/dev/rtl8730e-linux-sdk/sources/yocto/poky/bitbake/bin:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/hosttools" opkg-build -Z xz -a "--memlimit=50% --threads=8" openssl-ptest /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/deploy-ipks/cortexa32hf-neon' returned non-zero exit status 137.
Subprocess output:/home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/recipe-sysroot-native/usr/bin/opkg-build: line 317: 2279438 Done                    tar $ogargs $tsortargs --no-recursion $mtime_args -c $tarformat -T $tmp_dir/file_list
     2279439 Killed                  | $compressor $compressorargs > $tmp_dir/data.tar.$cext

ERROR: Logfile of failure stored in: /home/zivlow/dev/rtl8730e-linux-sdk/build_rtl8730elh-va8-generic/tmp/work/cortexa32hf-neon-rtk-linux-gnueabi/openssl/3.0.7-r0/temp/log.do_package_write_ipk.2276760
```

</details>

- Fix: simply re-run build command in the same shell after the shell has finished compiling other packages
```bash
m
```

# arm-rtk-linux-gnueabi-g++: fatal error: Killed signal terminated program cc1plus
- This error may occur when building with `m` command
- `Killed signal terminated program cc1plus` may indicate out of memory (OOM) scenario.
- Fix: Increase RAM or increase virtual memory (swap memory)

