/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <linux/device.h>
#include "wil_platform.h"
<<<<<<< HEAD
#include "msm_11ad.h"

int __init wil_platform_modinit(void)
{
	return msm_11ad_modinit();
=======

int __init wil_platform_modinit(void)
{
	return 0;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}

void wil_platform_modexit(void)
{
<<<<<<< HEAD
	msm_11ad_modexit();
=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}

/**
 * wil_platform_init() - wil6210 platform module init
 *
 * The function must be called before all other functions in this module.
 * It returns a handle which is used with the rest of the API
 *
 */
void *wil_platform_init(struct device *dev, struct wil_platform_ops *ops,
			const struct wil_platform_rops *rops, void *wil_handle)
{
<<<<<<< HEAD
	void *handle;
=======
	void *handle = ops; /* to return some non-NULL for 'void' impl. */
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

	if (!ops) {
		dev_err(dev,
			"Invalid parameter. Cannot init platform module\n");
		return NULL;
	}

<<<<<<< HEAD
	handle = msm_11ad_dev_init(dev, ops, rops, wil_handle);
=======
	/* platform specific init functions should be called here */
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

	return handle;
}
