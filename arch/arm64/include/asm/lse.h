/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_LSE_H
#define __ASM_LSE_H

#if defined(CONFIG_AS_LSE) && defined(CONFIG_ARM64_LSE_ATOMICS)

#include <linux/stringify.h>
#include <asm/alternative.h>

#ifdef __ASSEMBLER__

.arch_extension	lse

.macro alt_lse, llsc, lse
	alternative_insn "\llsc", "\lse", ARM64_HAS_LSE_ATOMICS
.endm

#else	/* __ASSEMBLER__ */

<<<<<<< HEAD
#ifdef CONFIG_LTO_CLANG
#define __LSE_PREAMBLE	".arch armv8-a+lse\n"
#else
__asm__(".arch_extension	lse");
#define __LSE_PREAMBLE
#endif
=======
__asm__(".arch_extension	lse");
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

/* Move the ll/sc atomics out-of-line */
#define __LL_SC_INLINE		notrace
#define __LL_SC_PREFIX(x)	__ll_sc_##x
#define __LL_SC_EXPORT(x)	EXPORT_SYMBOL(__LL_SC_PREFIX(x))

/* Macro for constructing calls to out-of-line ll/sc atomics */
#define __LL_SC_CALL(op)	"bl\t" __stringify(__LL_SC_PREFIX(op)) "\n"
#define __LL_SC_CLOBBERS	"x16", "x17", "x30"

/* In-line patching at runtime */
#define ARM64_LSE_ATOMIC_INSN(llsc, lse)				\
<<<<<<< HEAD
	ALTERNATIVE(llsc, __LSE_PREAMBLE lse, ARM64_HAS_LSE_ATOMICS)
=======
	ALTERNATIVE(llsc, lse, ARM64_HAS_LSE_ATOMICS)
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

#endif	/* __ASSEMBLER__ */
#else	/* CONFIG_AS_LSE && CONFIG_ARM64_LSE_ATOMICS */

#ifdef __ASSEMBLER__

.macro alt_lse, llsc, lse
	\llsc
.endm

#else	/* __ASSEMBLER__ */

#define __LL_SC_INLINE		static inline
#define __LL_SC_PREFIX(x)	x
#define __LL_SC_EXPORT(x)

#define ARM64_LSE_ATOMIC_INSN(llsc, lse)	llsc

#endif	/* __ASSEMBLER__ */
#endif	/* CONFIG_AS_LSE && CONFIG_ARM64_LSE_ATOMICS */
#endif	/* __ASM_LSE_H */
