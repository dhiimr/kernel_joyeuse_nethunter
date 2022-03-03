/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __QCOM_SMEM_H__
#define __QCOM_SMEM_H__

<<<<<<< HEAD
#include <linux/types.h>

=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
#define QCOM_SMEM_HOST_ANY -1

int qcom_smem_alloc(unsigned host, unsigned item, size_t size);
void *qcom_smem_get(unsigned host, unsigned item, size_t *size);

int qcom_smem_get_free_space(unsigned host);
<<<<<<< HEAD
phys_addr_t qcom_smem_virt_to_phys(void *addr);
=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

#endif
