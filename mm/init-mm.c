// SPDX-License-Identifier: GPL-2.0
#include <linux/mm_types.h>
#include <linux/rbtree.h>
#include <linux/rwsem.h>
#include <linux/spinlock.h>
#include <linux/list.h>
#include <linux/cpumask.h>

#include <linux/atomic.h>
#include <linux/user_namespace.h>
#include <asm/pgtable.h>
#include <asm/mmu.h>

#ifndef INIT_MM_CONTEXT
#define INIT_MM_CONTEXT(name)
#endif

struct mm_struct init_mm = {
	.mm_rb		= RB_ROOT,
<<<<<<< HEAD
#ifdef CONFIG_SPECULATIVE_PAGE_FAULT
	.mm_rb_lock	= __RW_LOCK_UNLOCKED(init_mm.mm_rb_lock),
#endif
=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	.pgd		= swapper_pg_dir,
	.mm_users	= ATOMIC_INIT(2),
	.mm_count	= ATOMIC_INIT(1),
	.mmap_sem	= __RWSEM_INITIALIZER(init_mm.mmap_sem),
	.page_table_lock =  __SPIN_LOCK_UNLOCKED(init_mm.page_table_lock),
<<<<<<< HEAD
	.arg_lock	=  __SPIN_LOCK_UNLOCKED(init_mm.arg_lock),
=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	.mmlist		= LIST_HEAD_INIT(init_mm.mmlist),
	.user_ns	= &init_user_ns,
	INIT_MM_CONTEXT(init_mm)
};
