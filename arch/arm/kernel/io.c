// SPDX-License-Identifier: GPL-2.0
#include <linux/export.h>
#include <linux/types.h>
#include <linux/io.h>
#include <linux/spinlock.h>

<<<<<<< HEAD
#define IO_CHECK_ALIGN(v, a) ((((unsigned long)(v)) & ((a) - 1)) == 0)

=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
static DEFINE_RAW_SPINLOCK(__io_lock);

/*
 * Generic atomic MMIO modify.
 *
 * Allows thread-safe access to registers shared by unrelated subsystems.
 * The access is protected by a single MMIO-wide lock.
 */
void atomic_io_modify_relaxed(void __iomem *reg, u32 mask, u32 set)
{
	unsigned long flags;
	u32 value;

	raw_spin_lock_irqsave(&__io_lock, flags);
	value = readl_relaxed(reg) & ~mask;
	value |= (set & mask);
	writel_relaxed(value, reg);
	raw_spin_unlock_irqrestore(&__io_lock, flags);
}
EXPORT_SYMBOL(atomic_io_modify_relaxed);

void atomic_io_modify(void __iomem *reg, u32 mask, u32 set)
{
	unsigned long flags;
	u32 value;

	raw_spin_lock_irqsave(&__io_lock, flags);
	value = readl_relaxed(reg) & ~mask;
	value |= (set & mask);
	writel(value, reg);
	raw_spin_unlock_irqrestore(&__io_lock, flags);
}
EXPORT_SYMBOL(atomic_io_modify);

/*
 * Copy data from IO memory space to "real" memory space.
<<<<<<< HEAD
 */
void _memcpy_fromio(void *to, const volatile void __iomem *from, size_t count)
{
	while (count && (!IO_CHECK_ALIGN(from, 8) || !IO_CHECK_ALIGN(to, 8))) {
		*(u8 *)to = readb_relaxed_no_log(from);
		from++;
		to++;
		count--;
	}

	while (count >= 8) {
		*(u64 *)to = readq_relaxed_no_log(from);
		from += 8;
		to += 8;
		count -= 8;
	}

	while (count) {
		*(u8 *)to = readb_relaxed_no_log(from);
		from++;
		to++;
		count--;
=======
 * This needs to be optimized.
 */
void _memcpy_fromio(void *to, const volatile void __iomem *from, size_t count)
{
	unsigned char *t = to;
	while (count) {
		count--;
		*t = readb(from);
		t++;
		from++;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	}
}
EXPORT_SYMBOL(_memcpy_fromio);

/*
 * Copy data from "real" memory space to IO memory space.
<<<<<<< HEAD
 */
void _memcpy_toio(volatile void __iomem *to, const void *from, size_t count)
{
	void *p = (void __force *)to;

	while (count && (!IO_CHECK_ALIGN(p, 8) || !IO_CHECK_ALIGN(from, 8))) {
		writeb_relaxed_no_log(*(volatile u8 *)from, p);
		from++;
		p++;
		count--;
	}

	while (count >= 8) {
		writeq_relaxed_no_log(*(volatile u64 *)from, p);
		from += 8;
		p += 8;
		count -= 8;
	}

	while (count) {
		writeb_relaxed_no_log(*(volatile u8 *)from, p);
		from++;
		p++;
		count--;
=======
 * This needs to be optimized.
 */
void _memcpy_toio(volatile void __iomem *to, const void *from, size_t count)
{
	const unsigned char *f = from;
	while (count) {
		count--;
		writeb(*f, to);
		f++;
		to++;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	}
}
EXPORT_SYMBOL(_memcpy_toio);

/*
 * "memset" on IO memory space.
<<<<<<< HEAD
 */
void _memset_io(volatile void __iomem *dst, int c, size_t count)
{
	void *p = (void __force *)dst;
	u64 qc = c;

	qc |= qc << 8;
	qc |= qc << 16;
	qc |= qc << 32;

	while (count && !IO_CHECK_ALIGN(p, 8)) {
		writeb_relaxed_no_log(c, p);
		p++;
		count--;
	}

	while (count >= 8) {
		writeq_relaxed_no_log(qc, p);
		p += 8;
		count -= 8;
	}

	while (count) {
		writeb_relaxed_no_log(c, p);
		p++;
		count--;
=======
 * This needs to be optimized.
 */
void _memset_io(volatile void __iomem *dst, int c, size_t count)
{
	while (count) {
		count--;
		writeb(c, dst);
		dst++;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	}
}
EXPORT_SYMBOL(_memset_io);
