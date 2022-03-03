/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_TIMERQUEUE_H
#define _LINUX_TIMERQUEUE_H

#include <linux/rbtree.h>
#include <linux/ktime.h>


struct timerqueue_node {
	struct rb_node node;
	ktime_t expires;
};

struct timerqueue_head {
<<<<<<< HEAD
	struct rb_root head;
	struct timerqueue_node *next;
=======
	struct rb_root_cached rb_root;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
};


extern bool timerqueue_add(struct timerqueue_head *head,
			   struct timerqueue_node *node);
extern bool timerqueue_del(struct timerqueue_head *head,
			   struct timerqueue_node *node);
extern struct timerqueue_node *timerqueue_iterate_next(
						struct timerqueue_node *node);

/**
 * timerqueue_getnext - Returns the timer with the earliest expiration time
 *
 * @head: head of timerqueue
 *
<<<<<<< HEAD
 * Returns a pointer to the timer node that has the
 * earliest expiration time.
=======
 * Returns a pointer to the timer node that has the earliest expiration time.
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
 */
static inline
struct timerqueue_node *timerqueue_getnext(struct timerqueue_head *head)
{
<<<<<<< HEAD
	return head->next;
=======
	struct rb_node *leftmost = rb_first_cached(&head->rb_root);

	return rb_entry(leftmost, struct timerqueue_node, node);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}

static inline void timerqueue_init(struct timerqueue_node *node)
{
	RB_CLEAR_NODE(&node->node);
}

static inline void timerqueue_init_head(struct timerqueue_head *head)
{
<<<<<<< HEAD
	head->head = RB_ROOT;
	head->next = NULL;
=======
	head->rb_root = RB_ROOT_CACHED;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}
#endif /* _LINUX_TIMERQUEUE_H */
