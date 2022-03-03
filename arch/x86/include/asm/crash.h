/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_CRASH_H
#define _ASM_X86_CRASH_H

<<<<<<< HEAD
=======
struct kimage;

>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
int crash_load_segments(struct kimage *image);
int crash_copy_backup_region(struct kimage *image);
int crash_setup_memmap_entries(struct kimage *image,
		struct boot_params *params);

#endif /* _ASM_X86_CRASH_H */
