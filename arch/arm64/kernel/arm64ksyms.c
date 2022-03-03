/*
 * Based on arch/arm/kernel/armksyms.c
 *
 * Copyright (C) 2000 Russell King
 * Copyright (C) 2012 ARM Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/export.h>
#include <linux/sched.h>
#include <linux/string.h>
#include <linux/cryptohash.h>
#include <linux/delay.h>
#include <linux/in6.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/arm-smccc.h>
#include <linux/kprobes.h>

<<<<<<< HEAD
#include <asm/cacheflush.h>
=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
#include <asm/checksum.h>

EXPORT_SYMBOL(copy_page);
EXPORT_SYMBOL(clear_page);

	/* user mem (segment) */
EXPORT_SYMBOL(__arch_copy_from_user);
EXPORT_SYMBOL(__arch_copy_to_user);
EXPORT_SYMBOL(__arch_clear_user);
EXPORT_SYMBOL(__arch_copy_in_user);

	/* physical memory */
EXPORT_SYMBOL(memstart_addr);

	/* string / mem functions */
<<<<<<< HEAD
=======
#ifndef CONFIG_KASAN
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
EXPORT_SYMBOL(strchr);
EXPORT_SYMBOL(strrchr);
EXPORT_SYMBOL(strcmp);
EXPORT_SYMBOL(strncmp);
EXPORT_SYMBOL(strlen);
EXPORT_SYMBOL(strnlen);
<<<<<<< HEAD
=======
EXPORT_SYMBOL(memcmp);
EXPORT_SYMBOL(memchr);
#endif

>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
EXPORT_SYMBOL(memset);
EXPORT_SYMBOL(memcpy);
EXPORT_SYMBOL(memmove);
EXPORT_SYMBOL(__memset);
EXPORT_SYMBOL(__memcpy);
EXPORT_SYMBOL(__memmove);
<<<<<<< HEAD
EXPORT_SYMBOL(memchr);
EXPORT_SYMBOL(memcmp);
=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

	/* atomic bitops */
EXPORT_SYMBOL(set_bit);
EXPORT_SYMBOL(test_and_set_bit);
EXPORT_SYMBOL(clear_bit);
EXPORT_SYMBOL(test_and_clear_bit);
EXPORT_SYMBOL(change_bit);
EXPORT_SYMBOL(test_and_change_bit);

#ifdef CONFIG_FUNCTION_TRACER
EXPORT_SYMBOL(_mcount);
NOKPROBE_SYMBOL(_mcount);
#endif

	/* arm-smccc */
EXPORT_SYMBOL(__arm_smccc_smc);
EXPORT_SYMBOL(__arm_smccc_hvc);
<<<<<<< HEAD

	/* caching functions */
EXPORT_SYMBOL(__dma_inv_area);
EXPORT_SYMBOL(__dma_clean_area);
EXPORT_SYMBOL(__dma_flush_area);
=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
