/*
 * Copyright 2013, Michael Ellerman, IBM Corporation.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#define pr_fmt(fmt)	"pseries-rng: " fmt

#include <linux/kernel.h>
#include <linux/of.h>
#include <asm/archrandom.h>
#include <asm/machdep.h>
#include <asm/plpar_wrappers.h>


static int pseries_get_random_long(unsigned long *v)
{
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];

	if (plpar_hcall(H_RANDOM, retbuf) == H_SUCCESS) {
		*v = retbuf[0];
		return 1;
	}

	return 0;
}

static __init int rng_init(void)
{
	struct device_node *dn;

	dn = of_find_compatible_node(NULL, NULL, "ibm,random");
	if (!dn)
		return -ENODEV;

	pr_info("Registering arch random hook.\n");

	ppc_md.get_random_seed = pseries_get_random_long;

<<<<<<< HEAD
=======
	of_node_put(dn);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	return 0;
}
machine_subsys_initcall(pseries, rng_init);
