# SPDX-License-Identifier: GPL-2.0
noarg:
	$(MAKE) -C ../

TEST_GEN_PROGS := hugetlb_vs_thp_test subpage_prot prot_sao
<<<<<<< HEAD
=======
TEST_GEN_PROGS_EXTENDED := tlbie_test
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
TEST_GEN_FILES := tempfile

include ../../lib.mk

$(TEST_GEN_PROGS): ../harness.c

$(OUTPUT)/prot_sao: ../utils.c

$(OUTPUT)/tempfile:
	dd if=/dev/zero of=$@ bs=64k count=1

<<<<<<< HEAD
=======
$(OUTPUT)/tlbie_test: LDLIBS += -lpthread
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
