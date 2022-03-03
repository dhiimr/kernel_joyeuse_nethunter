/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_GENERIC_QRWLOCK_TYPES_H
#define __ASM_GENERIC_QRWLOCK_TYPES_H

#include <linux/types.h>
#include <asm/spinlock_types.h>

/*
 * The queue read/write lock data structure
 */

typedef struct qrwlock {
<<<<<<< HEAD
	union {
		atomic_t cnts;
		struct {
#ifdef __LITTLE_ENDIAN
			u8 wlocked;	/* Locked for write? */
			u8 __lstate[3];
#else
			u8 __lstate[3];
			u8 wlocked;	/* Locked for write? */
#endif
		};
	};
=======
	atomic_t		cnts;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	arch_spinlock_t		wait_lock;
} arch_rwlock_t;

#define	__ARCH_RW_LOCK_UNLOCKED {		\
<<<<<<< HEAD
	{ .cnts = ATOMIC_INIT(0), },		\
=======
	.cnts = ATOMIC_INIT(0),			\
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	.wait_lock = __ARCH_SPIN_LOCK_UNLOCKED,	\
}

#endif /* __ASM_GENERIC_QRWLOCK_TYPES_H */
