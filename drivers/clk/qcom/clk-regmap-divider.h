/*
<<<<<<< HEAD
 * Copyright (c) 2014, 2017, The Linux Foundation. All rights reserved.
=======
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __QCOM_CLK_REGMAP_DIVIDER_H__
#define __QCOM_CLK_REGMAP_DIVIDER_H__

#include <linux/clk-provider.h>
#include "clk-regmap.h"

struct clk_regmap_div {
<<<<<<< HEAD
	u32				reg;
	u32				shift;
	u32				width;
	u32				flags;
	const struct clk_div_table	*table;
	struct clk_regmap		clkr;
=======
	u32			reg;
	u32			shift;
	u32			width;
	struct clk_regmap	clkr;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
};

extern const struct clk_ops clk_regmap_div_ops;

#endif
