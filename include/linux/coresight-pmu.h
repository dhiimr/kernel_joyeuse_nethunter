/*
 * Copyright(C) 2015 Linaro Limited. All rights reserved.
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _LINUX_CORESIGHT_PMU_H
#define _LINUX_CORESIGHT_PMU_H

#define CORESIGHT_ETM_PMU_NAME "cs_etm"
<<<<<<< HEAD
#define CORESIGHT_ETM_PMU_SEED  0x01
=======
#define CORESIGHT_ETM_PMU_SEED  0x10
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

/* ETMv3.5/PTM's ETMCR config bit */
#define ETM_OPT_CYCACC  12
#define ETM_OPT_TS      28
#define ETM_OPT_RETSTK	29

/* ETMv4 CONFIGR programming bits for the ETM OPTs */
#define ETM4_CFG_BIT_CYCACC	4
#define ETM4_CFG_BIT_TS		11
#define ETM4_CFG_BIT_RETSTK	12

static inline int coresight_get_trace_id(int cpu)
{
	/*
	 * A trace ID of value 0 is invalid, so let's start at some
	 * random value that fits in 7 bits and go from there.  Since
	 * the common convention is to have data trace IDs be I(N) + 1,
	 * set instruction trace IDs as a function of the CPU number.
	 */
<<<<<<< HEAD
	return (CORESIGHT_ETM_PMU_SEED + cpu);
=======
	return (CORESIGHT_ETM_PMU_SEED + (cpu * 2));
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}

#endif
