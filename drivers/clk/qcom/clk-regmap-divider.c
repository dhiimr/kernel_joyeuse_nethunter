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

#include <linux/kernel.h>
#include <linux/bitops.h>
#include <linux/regmap.h>
#include <linux/export.h>

#include "clk-regmap-divider.h"

static inline struct clk_regmap_div *to_clk_regmap_div(struct clk_hw *hw)
{
	return container_of(to_clk_regmap(hw), struct clk_regmap_div, clkr);
}

static long div_round_rate(struct clk_hw *hw, unsigned long rate,
			   unsigned long *prate)
{
	struct clk_regmap_div *divider = to_clk_regmap_div(hw);

<<<<<<< HEAD
	return divider_round_rate(hw, rate, prate, divider->table,
				  divider->width,
				  CLK_DIVIDER_ROUND_CLOSEST |
				  divider->flags);
=======
	return divider_round_rate(hw, rate, prate, NULL, divider->width,
				  CLK_DIVIDER_ROUND_CLOSEST);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}

static int div_set_rate(struct clk_hw *hw, unsigned long rate,
			unsigned long parent_rate)
{
	struct clk_regmap_div *divider = to_clk_regmap_div(hw);
	struct clk_regmap *clkr = &divider->clkr;
	u32 div;

<<<<<<< HEAD
	div = divider_get_val(rate, parent_rate, divider->table,
			      divider->width, CLK_DIVIDER_ROUND_CLOSEST |
			      divider->flags);
=======
	div = divider_get_val(rate, parent_rate, NULL, divider->width,
			      CLK_DIVIDER_ROUND_CLOSEST);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

	return regmap_update_bits(clkr->regmap, divider->reg,
				  (BIT(divider->width) - 1) << divider->shift,
				  div << divider->shift);
}

static unsigned long div_recalc_rate(struct clk_hw *hw,
				     unsigned long parent_rate)
{
	struct clk_regmap_div *divider = to_clk_regmap_div(hw);
	struct clk_regmap *clkr = &divider->clkr;
	u32 div;

	regmap_read(clkr->regmap, divider->reg, &div);
	div >>= divider->shift;
	div &= BIT(divider->width) - 1;

<<<<<<< HEAD
	return divider_recalc_rate(hw, parent_rate, div, divider->table,
				   CLK_DIVIDER_ROUND_CLOSEST | divider->flags,
				   divider->width);
=======
	return divider_recalc_rate(hw, parent_rate, div, NULL,
				   CLK_DIVIDER_ROUND_CLOSEST, divider->width);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}

const struct clk_ops clk_regmap_div_ops = {
	.round_rate = div_round_rate,
	.set_rate = div_set_rate,
	.recalc_rate = div_recalc_rate,
};
EXPORT_SYMBOL_GPL(clk_regmap_div_ops);
