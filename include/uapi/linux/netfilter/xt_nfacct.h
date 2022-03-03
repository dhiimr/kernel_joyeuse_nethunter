/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _XT_NFACCT_MATCH_H
#define _XT_NFACCT_MATCH_H

#include <linux/netfilter/nfnetlink_acct.h>

struct nf_acct;

struct xt_nfacct_match_info {
	char		name[NFACCT_NAME_MAX];
	struct nf_acct	*nfacct;
};

<<<<<<< HEAD
=======
struct xt_nfacct_match_info_v1 {
	char		name[NFACCT_NAME_MAX];
	struct nf_acct	*nfacct __attribute__((aligned(8)));
};

>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
#endif /* _XT_NFACCT_MATCH_H */
