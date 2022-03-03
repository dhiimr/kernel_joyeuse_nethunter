<<<<<<< HEAD
/* Copyright (c) 2015, 2019, The Linux Foundation. All rights reserved.
=======
/* Copyright (c) 2015, The Linux Foundation. All rights reserved.
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef UFSHCD_PLTFRM_H_
#define UFSHCD_PLTFRM_H_

#include "ufshcd.h"

int ufshcd_pltfrm_init(struct platform_device *pdev,
<<<<<<< HEAD
		       struct ufs_hba_variant *var);
=======
		       struct ufs_hba_variant_ops *vops);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
void ufshcd_pltfrm_shutdown(struct platform_device *pdev);

#ifdef CONFIG_PM

int ufshcd_pltfrm_suspend(struct device *dev);
int ufshcd_pltfrm_resume(struct device *dev);
int ufshcd_pltfrm_runtime_suspend(struct device *dev);
int ufshcd_pltfrm_runtime_resume(struct device *dev);
int ufshcd_pltfrm_runtime_idle(struct device *dev);
<<<<<<< HEAD
int ufshcd_pltfrm_freeze(struct device *dev);
int ufshcd_pltfrm_restore(struct device *dev);
int ufshcd_pltfrm_thaw(struct device *dev);
=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

#else /* !CONFIG_PM */

#define ufshcd_pltfrm_suspend	NULL
#define ufshcd_pltfrm_resume	NULL
#define ufshcd_pltfrm_runtime_suspend	NULL
#define ufshcd_pltfrm_runtime_resume	NULL
#define ufshcd_pltfrm_runtime_idle	NULL

#endif /* CONFIG_PM */

#endif /* UFSHCD_PLTFRM_H_ */
