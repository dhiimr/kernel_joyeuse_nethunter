# SPDX-License-Identifier: GPL-2.0
<<<<<<< HEAD
TEST_PROGS := signal signal_tm

all: $(TEST_PROGS)

$(TEST_PROGS): ../harness.c ../utils.c signal.S

CFLAGS += -maltivec
signal_tm: CFLAGS += -mhtm

include ../../lib.mk

clean:
	rm -f $(TEST_PROGS) *.o
=======
TEST_GEN_PROGS := signal signal_tm

CFLAGS += -maltivec
$(OUTPUT)/signal_tm: CFLAGS += -mhtm

include ../../lib.mk

$(TEST_GEN_PROGS): ../harness.c ../utils.c signal.S
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
