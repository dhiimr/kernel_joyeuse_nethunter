# SPDX-License-Identifier: GPL-2.0
###
# scripts contains sources for various helper programs used throughout
# the kernel for the build process.
# ---------------------------------------------------------------------------
# kallsyms:      Find all symbols in vmlinux
# pnmttologo:    Convert pnm files to logo files
# conmakehash:   Create chartable
# conmakehash:	 Create arrays for initializing the kernel console tables

HOST_EXTRACFLAGS += -I$(srctree)/tools/include

<<<<<<< HEAD
=======
CRYPTO_LIBS = $(shell pkg-config --libs libcrypto 2> /dev/null || echo -lcrypto)
CRYPTO_CFLAGS = $(shell pkg-config --cflags libcrypto 2> /dev/null)

>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
hostprogs-$(CONFIG_KALLSYMS)     += kallsyms
hostprogs-$(CONFIG_LOGO)         += pnmtologo
hostprogs-$(CONFIG_VT)           += conmakehash
hostprogs-$(BUILD_C_RECORDMCOUNT) += recordmcount
hostprogs-$(CONFIG_BUILDTIME_EXTABLE_SORT) += sortextable
hostprogs-$(CONFIG_ASN1)	 += asn1_compiler
hostprogs-$(CONFIG_MODULE_SIG)	 += sign-file
hostprogs-$(CONFIG_SYSTEM_TRUSTED_KEYRING) += extract-cert
hostprogs-$(CONFIG_SYSTEM_EXTRA_CERTIFICATE) += insert-sys-cert

HOSTCFLAGS_sortextable.o = -I$(srctree)/tools/include
HOSTCFLAGS_asn1_compiler.o = -I$(srctree)/include
<<<<<<< HEAD
HOSTLOADLIBES_sign-file = -lcrypto
HOSTLOADLIBES_extract-cert = -lcrypto
=======
HOSTCFLAGS_sign-file.o = $(CRYPTO_CFLAGS)
HOSTLOADLIBES_sign-file = $(CRYPTO_LIBS)
HOSTCFLAGS_extract-cert.o = $(CRYPTO_CFLAGS)
HOSTLOADLIBES_extract-cert = $(CRYPTO_LIBS)
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

always		:= $(hostprogs-y) $(hostprogs-m)

# The following hostprogs-y programs are only build on demand
hostprogs-y += unifdef

# These targets are used internally to avoid "is up to date" messages
PHONY += build_unifdef
build_unifdef: $(obj)/unifdef
	@:

subdir-$(CONFIG_MODVERSIONS) += genksyms
subdir-y                     += mod
subdir-$(CONFIG_SECURITY_SELINUX) += selinux
<<<<<<< HEAD
subdir-$(CONFIG_DTC)         += dtc-aosp
=======
subdir-$(CONFIG_DTC)         += dtc
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
subdir-$(CONFIG_GDB_SCRIPTS) += gdb

# Let clean descend into subdirs
subdir-	+= basic kconfig package gcc-plugins
