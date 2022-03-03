/*
 * Queued read/write locks
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * (C) Copyright 2013-2014 Hewlett-Packard Development Company, L.P.
 *
 * Authors: Waiman Long <waiman.long@hp.com>
 */
#include <linux/smp.h>
#include <linux/bug.h>
#include <linux/cpumask.h>
#include <linux/percpu.h>
#include <linux/hardirq.h>
#include <linux/spinlock.h>
#include <asm/qrwlock.h>

<<<<<<< HEAD
/**
 * queued_read_lock_slowpath - acquire read lock of a queue rwlock
 * @lock: Pointer to queue rwlock structure
 */
void queued_read_lock_slowpath(struct qrwlock *lock)
=======
/*
 * This internal data structure is used for optimizing access to some of
 * the subfields within the atomic_t cnts.
 */
struct __qrwlock {
	union {
		atomic_t cnts;
		struct {
#ifdef __LITTLE_ENDIAN
			u8 wmode;	/* Writer mode   */
			u8 rcnts[3];	/* Reader counts */
#else
			u8 rcnts[3];	/* Reader counts */
			u8 wmode;	/* Writer mode   */
#endif
		};
	};
	arch_spinlock_t	lock;
};

/**
 * rspin_until_writer_unlock - inc reader count & spin until writer is gone
 * @lock  : Pointer to queue rwlock structure
 * @writer: Current queue rwlock writer status byte
 *
 * In interrupt context or at the head of the queue, the reader will just
 * increment the reader count & wait until the writer releases the lock.
 */
static __always_inline void
rspin_until_writer_unlock(struct qrwlock *lock, u32 cnts)
{
	while ((cnts & _QW_WMASK) == _QW_LOCKED) {
		cpu_relax();
		cnts = atomic_read_acquire(&lock->cnts);
	}
}

/**
 * queued_read_lock_slowpath - acquire read lock of a queue rwlock
 * @lock: Pointer to queue rwlock structure
 * @cnts: Current qrwlock lock value
 */
void queued_read_lock_slowpath(struct qrwlock *lock, u32 cnts)
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
{
	/*
	 * Readers come here when they cannot get the lock without waiting
	 */
	if (unlikely(in_interrupt())) {
		/*
		 * Readers in interrupt context will get the lock immediately
<<<<<<< HEAD
		 * if the writer is just waiting (not holding the lock yet),
		 * so spin with ACQUIRE semantics until the lock is available
		 * without waiting in the queue.
		 */
		atomic_cond_read_acquire(&lock->cnts, !(VAL & _QW_LOCKED));
=======
		 * if the writer is just waiting (not holding the lock yet).
		 * The rspin_until_writer_unlock() function returns immediately
		 * in this case. Otherwise, they will spin (with ACQUIRE
		 * semantics) until the lock is available without waiting in
		 * the queue.
		 */
		rspin_until_writer_unlock(lock, cnts);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		return;
	}
	atomic_sub(_QR_BIAS, &lock->cnts);

	/*
	 * Put the reader into the wait queue
	 */
	arch_spin_lock(&lock->wait_lock);
<<<<<<< HEAD
	atomic_add(_QR_BIAS, &lock->cnts);
=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

	/*
	 * The ACQUIRE semantics of the following spinning code ensure
	 * that accesses can't leak upwards out of our subsequent critical
	 * section in the case that the lock is currently held for write.
	 */
<<<<<<< HEAD
	atomic_cond_read_acquire(&lock->cnts, !(VAL & _QW_LOCKED));
=======
	cnts = atomic_fetch_add_acquire(_QR_BIAS, &lock->cnts);
	rspin_until_writer_unlock(lock, cnts);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

	/*
	 * Signal the next one in queue to become queue head
	 */
	arch_spin_unlock(&lock->wait_lock);
}
EXPORT_SYMBOL(queued_read_lock_slowpath);

/**
 * queued_write_lock_slowpath - acquire write lock of a queue rwlock
 * @lock : Pointer to queue rwlock structure
 */
void queued_write_lock_slowpath(struct qrwlock *lock)
{
<<<<<<< HEAD
=======
	u32 cnts;

>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	/* Put the writer into the wait queue */
	arch_spin_lock(&lock->wait_lock);

	/* Try to acquire the lock directly if no reader is present */
	if (!atomic_read(&lock->cnts) &&
	    (atomic_cmpxchg_acquire(&lock->cnts, 0, _QW_LOCKED) == 0))
		goto unlock;

<<<<<<< HEAD
	/* Set the waiting flag to notify readers that a writer is pending */
	atomic_add(_QW_WAITING, &lock->cnts);

	/* When no more readers or writers, set the locked flag */
	do {
		atomic_cond_read_acquire(&lock->cnts, VAL == _QW_WAITING);
	} while (atomic_cmpxchg_relaxed(&lock->cnts, _QW_WAITING,
					_QW_LOCKED) != _QW_WAITING);
=======
	/*
	 * Set the waiting flag to notify readers that a writer is pending,
	 * or wait for a previous writer to go away.
	 */
	for (;;) {
		struct __qrwlock *l = (struct __qrwlock *)lock;

		if (!READ_ONCE(l->wmode) &&
		   (cmpxchg_relaxed(&l->wmode, 0, _QW_WAITING) == 0))
			break;

		cpu_relax();
	}

	/* When no more readers, set the locked flag */
	for (;;) {
		cnts = atomic_read(&lock->cnts);
		if ((cnts == _QW_WAITING) &&
		    (atomic_cmpxchg_acquire(&lock->cnts, _QW_WAITING,
					    _QW_LOCKED) == _QW_WAITING))
			break;

		cpu_relax();
	}
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
unlock:
	arch_spin_unlock(&lock->wait_lock);
}
EXPORT_SYMBOL(queued_write_lock_slowpath);
