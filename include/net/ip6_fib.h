/*
 *	Linux INET6 implementation 
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>	
 *
 *	This program is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      2 of the License, or (at your option) any later version.
 */

#ifndef _IP6_FIB_H
#define _IP6_FIB_H

#include <linux/ipv6_route.h>
#include <linux/rtnetlink.h>
#include <linux/spinlock.h>
#include <linux/notifier.h>
#include <net/dst.h>
#include <net/flow.h>
#include <net/netlink.h>
#include <net/inetpeer.h>
#include <net/fib_notifier.h>

#ifdef CONFIG_IPV6_MULTIPLE_TABLES
#define FIB6_TABLE_HASHSZ 256
#else
#define FIB6_TABLE_HASHSZ 1
#endif

struct rt6_info;

struct fib6_config {
	u32		fc_table;
	u32		fc_metric;
	int		fc_dst_len;
	int		fc_src_len;
	int		fc_ifindex;
	u32		fc_flags;
	u32		fc_protocol;
	u16		fc_type;        /* only 8 bits are used */
	u16		fc_delete_all_nh : 1,
			__unused : 15;

	struct in6_addr	fc_dst;
	struct in6_addr	fc_src;
	struct in6_addr	fc_prefsrc;
	struct in6_addr	fc_gateway;

	unsigned long	fc_expires;
	struct nlattr	*fc_mx;
	int		fc_mx_len;
	int		fc_mp_len;
	struct nlattr	*fc_mp;

	struct nl_info	fc_nlinfo;
	struct nlattr	*fc_encap;
	u16		fc_encap_type;
};

struct fib6_node {
	struct fib6_node	*parent;
	struct fib6_node	*left;
	struct fib6_node	*right;
#ifdef CONFIG_IPV6_SUBTREES
	struct fib6_node	*subtree;
#endif
	struct rt6_info		*leaf;

	__u16			fn_bit;		/* bit key */
	__u16			fn_flags;
	int			fn_sernum;
	struct rt6_info		*rr_ptr;
	struct rcu_head		rcu;
};

#ifndef CONFIG_IPV6_SUBTREES
#define FIB6_SUBTREE(fn)	NULL
#else
#define FIB6_SUBTREE(fn)	((fn)->subtree)
#endif

struct mx6_config {
	const u32 *mx;
	DECLARE_BITMAP(mx_valid, RTAX_MAX);
};

/*
 *	routing information
 *
 */

struct rt6key {
	struct in6_addr	addr;
	int		plen;
};

struct fib6_table;

struct rt6_info {
	struct dst_entry		dst;

	/*
	 * Tail elements of dst_entry (__refcnt etc.)
	 * and these elements (rarely used in hot path) are in
	 * the same cache line.
	 */
	struct fib6_table		*rt6i_table;
	struct fib6_node __rcu		*rt6i_node;

	struct in6_addr			rt6i_gateway;

	/* Multipath routes:
	 * siblings is a list of rt6_info that have the the same metric/weight,
	 * destination, but not the same gateway. nsiblings is just a cache
	 * to speed up lookup.
	 */
	struct list_head		rt6i_siblings;
	unsigned int			rt6i_nsiblings;

	atomic_t			rt6i_ref;

	unsigned int			rt6i_nh_flags;

	/* These are in a separate cache line. */
	struct rt6key			rt6i_dst ____cacheline_aligned_in_smp;
	u32				rt6i_flags;
	struct rt6key			rt6i_src;
	struct rt6key			rt6i_prefsrc;

	struct list_head		rt6i_uncached;
	struct uncached_list		*rt6i_uncached_list;

	struct inet6_dev		*rt6i_idev;
	struct rt6_info * __percpu	*rt6i_pcpu;

	u32				rt6i_metric;
	u32				rt6i_pmtu;
	/* more non-fragment space at head required */
	unsigned short			rt6i_nfheader_len;
	u8				rt6i_protocol;
};

static inline struct inet6_dev *ip6_dst_idev(struct dst_entry *dst)
{
	return ((struct rt6_info *)dst)->rt6i_idev;
}

static inline void rt6_clean_expires(struct rt6_info *rt)
{
	rt->rt6i_flags &= ~RTF_EXPIRES;
	rt->dst.expires = 0;
}

static inline void rt6_set_expires(struct rt6_info *rt, unsigned long expires)
{
	rt->dst.expires = expires;
	rt->rt6i_flags |= RTF_EXPIRES;
}

static inline void rt6_update_expires(struct rt6_info *rt0, int timeout)
{
	struct rt6_info *rt;

	for (rt = rt0; rt && !(rt->rt6i_flags & RTF_EXPIRES);
	     rt = (struct rt6_info *)rt->dst.from);
	if (rt && rt != rt0)
		rt0->dst.expires = rt->dst.expires;

	dst_set_expires(&rt0->dst, timeout);
	rt0->rt6i_flags |= RTF_EXPIRES;
}

/* Function to safely get fn->sernum for passed in rt
 * and store result in passed in cookie.
 * Return true if we can get cookie safely
 * Return false if not
 */
static inline bool rt6_get_cookie_safe(const struct rt6_info *rt,
				       u32 *cookie)
{
	struct fib6_node *fn;
	bool status = false;

	rcu_read_lock();
	fn = rcu_dereference(rt->rt6i_node);

	if (fn) {
		*cookie = fn->fn_sernum;
		status = true;
	}

	rcu_read_unlock();
	return status;
}

static inline u32 rt6_get_cookie(const struct rt6_info *rt)
{
	u32 cookie = 0;

<<<<<<< HEAD
	if (rt->rt6i_flags & RTF_PCPU ||
	    (unlikely(!list_empty(&rt->rt6i_uncached)) && rt->dst.from))
=======
	if (rt->dst.from)
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		rt = (struct rt6_info *)(rt->dst.from);

	rt6_get_cookie_safe(rt, &cookie);

	return cookie;
}

static inline void ip6_rt_put(struct rt6_info *rt)
{
	/* dst_release() accepts a NULL parameter.
	 * We rely on dst being first structure in struct rt6_info
	 */
	BUILD_BUG_ON(offsetof(struct rt6_info, dst) != 0);
	dst_release(&rt->dst);
}

void rt6_free_pcpu(struct rt6_info *non_pcpu_rt);

static inline void rt6_hold(struct rt6_info *rt)
{
	atomic_inc(&rt->rt6i_ref);
}

static inline void rt6_release(struct rt6_info *rt)
{
	if (atomic_dec_and_test(&rt->rt6i_ref)) {
		rt6_free_pcpu(rt);
		dst_dev_put(&rt->dst);
		dst_release(&rt->dst);
	}
}

enum fib6_walk_state {
#ifdef CONFIG_IPV6_SUBTREES
	FWS_S,
#endif
	FWS_L,
	FWS_R,
	FWS_C,
	FWS_U
};

struct fib6_walker {
	struct list_head lh;
	struct fib6_node *root, *node;
	struct rt6_info *leaf;
	enum fib6_walk_state state;
	bool prune;
	unsigned int skip;
	unsigned int count;
	int (*func)(struct fib6_walker *);
	void *args;
};

struct rt6_statistics {
	__u32		fib_nodes;
	__u32		fib_route_nodes;
	__u32		fib_rt_alloc;		/* permanent routes	*/
	__u32		fib_rt_entries;		/* rt entries in table	*/
	__u32		fib_rt_cache;		/* cache routes		*/
	__u32		fib_discarded_routes;
};

#define RTN_TL_ROOT	0x0001
#define RTN_ROOT	0x0002		/* tree root node		*/
#define RTN_RTINFO	0x0004		/* node with valid routing info	*/

/*
 *	priority levels (or metrics)
 *
 */


struct fib6_table {
	struct hlist_node	tb6_hlist;
	u32			tb6_id;
	rwlock_t		tb6_lock;
	struct fib6_node	tb6_root;
	struct inet_peer_base	tb6_peers;
	unsigned int		flags;
	unsigned int		fib_seq;
#define RT6_TABLE_HAS_DFLT_ROUTER	BIT(0)
};

#define RT6_TABLE_UNSPEC	RT_TABLE_UNSPEC
#define RT6_TABLE_MAIN		RT_TABLE_MAIN
#define RT6_TABLE_DFLT		RT6_TABLE_MAIN
#define RT6_TABLE_INFO		RT6_TABLE_MAIN
#define RT6_TABLE_PREFIX	RT6_TABLE_MAIN

#ifdef CONFIG_IPV6_MULTIPLE_TABLES
#define FIB6_TABLE_MIN		1
#define FIB6_TABLE_MAX		RT_TABLE_MAX
#define RT6_TABLE_LOCAL		RT_TABLE_LOCAL
#else
#define FIB6_TABLE_MIN		RT_TABLE_MAIN
#define FIB6_TABLE_MAX		FIB6_TABLE_MIN
#define RT6_TABLE_LOCAL		RT6_TABLE_MAIN
#endif

typedef struct rt6_info *(*pol_lookup_t)(struct net *,
					 struct fib6_table *,
					 struct flowi6 *, int);

struct fib6_entry_notifier_info {
	struct fib_notifier_info info; /* must be first */
	struct rt6_info *rt;
};

/*
 *	exported functions
 */

struct fib6_table *fib6_get_table(struct net *net, u32 id);
struct fib6_table *fib6_new_table(struct net *net, u32 id);
struct dst_entry *fib6_rule_lookup(struct net *net, struct flowi6 *fl6,
				   int flags, pol_lookup_t lookup);

struct fib6_node *fib6_lookup(struct fib6_node *root,
			      const struct in6_addr *daddr,
			      const struct in6_addr *saddr);

struct fib6_node *fib6_locate(struct fib6_node *root,
			      const struct in6_addr *daddr, int dst_len,
			      const struct in6_addr *saddr, int src_len);

void fib6_clean_all(struct net *net, int (*func)(struct rt6_info *, void *arg),
		    void *arg);

int fib6_add(struct fib6_node *root, struct rt6_info *rt,
	     struct nl_info *info, struct mx6_config *mxc,
	     struct netlink_ext_ack *extack);
int fib6_del(struct rt6_info *rt, struct nl_info *info);

void inet6_rt_notify(int event, struct rt6_info *rt, struct nl_info *info,
		     unsigned int flags);

void fib6_run_gc(unsigned long expires, struct net *net, bool force);

void fib6_gc_cleanup(void);

int fib6_init(void);

int ipv6_route_open(struct inode *inode, struct file *file);

int call_fib6_notifier(struct notifier_block *nb, struct net *net,
		       enum fib_event_type event_type,
		       struct fib_notifier_info *info);
int call_fib6_notifiers(struct net *net, enum fib_event_type event_type,
			struct fib_notifier_info *info);

int __net_init fib6_notifier_init(struct net *net);
void __net_exit fib6_notifier_exit(struct net *net);

unsigned int fib6_tables_seq_read(struct net *net);
int fib6_tables_dump(struct net *net, struct notifier_block *nb);

#ifdef CONFIG_IPV6_MULTIPLE_TABLES
int fib6_rules_init(void);
void fib6_rules_cleanup(void);
bool fib6_rule_default(const struct fib_rule *rule);
int fib6_rules_dump(struct net *net, struct notifier_block *nb);
unsigned int fib6_rules_seq_read(struct net *net);
#else
static inline int               fib6_rules_init(void)
{
	return 0;
}
static inline void              fib6_rules_cleanup(void)
{
	return ;
}
static inline bool fib6_rule_default(const struct fib_rule *rule)
{
	return true;
}
static inline int fib6_rules_dump(struct net *net, struct notifier_block *nb)
{
	return 0;
}
static inline unsigned int fib6_rules_seq_read(struct net *net)
{
	return 0;
}
#endif
#endif
