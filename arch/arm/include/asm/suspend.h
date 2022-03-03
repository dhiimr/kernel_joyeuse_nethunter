/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_ARM_SUSPEND_H
#define __ASM_ARM_SUSPEND_H

#include <linux/types.h>

struct sleep_save_sp {
	u32 *save_ptr_stash;
	u32 save_ptr_stash_phys;
};

extern void cpu_resume(void);
<<<<<<< HEAD
=======
extern void cpu_resume_no_hyp(void);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
extern void cpu_resume_arm(void);
extern int cpu_suspend(unsigned long, int (*)(unsigned long));

#endif
