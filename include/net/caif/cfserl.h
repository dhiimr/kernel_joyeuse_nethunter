/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 * License terms: GNU General Public License (GPL) version 2
 */

#ifndef CFSERL_H_
#define CFSERL_H_
#include <net/caif/caif_layer.h>

struct cflayer *cfserl_create(int instance, bool use_stx);
<<<<<<< HEAD
=======
void cfserl_release(struct cflayer *layer);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
#endif
