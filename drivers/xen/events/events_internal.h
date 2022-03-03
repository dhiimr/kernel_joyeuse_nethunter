/*
 * Xen Event Channels (internal header)
 *
 * Copyright (C) 2013 Citrix Systems R&D Ltd.
 *
 * This source code is licensed under the GNU General Public License,
 * Version 2 or later.  See the file COPYING for more details.
 */
#ifndef __EVENTS_INTERNAL_H__
#define __EVENTS_INTERNAL_H__

/* Interrupt types. */
enum xen_irq_type {
	IRQT_UNBOUND = 0,
	IRQT_PIRQ,
	IRQT_VIRQ,
	IRQT_IPI,
	IRQT_EVTCHN
};

/*
 * Packed IRQ information:
 * type - enum xen_irq_type
 * event channel - irq->event channel mapping
 * cpu - cpu this event channel is bound to
 * index - type-specific information:
 *    PIRQ - vector, with MSB being "needs EIO", or physical IRQ of the HVM
 *           guest, or GSI (real passthrough IRQ) of the device.
 *    VIRQ - virq number
 *    IPI - IPI vector
 *    EVTCHN -
 */
struct irq_info {
	struct list_head list;
<<<<<<< HEAD
	int refcnt;
	enum xen_irq_type type;	/* type */
	unsigned irq;
	unsigned int evtchn;	/* event channel */
	unsigned short cpu;	/* cpu bound */
=======
	struct list_head eoi_list;
	short refcnt;
	short spurious_cnt;
	short type;		/* type */
	u8 mask_reason;		/* Why is event channel masked */
#define EVT_MASK_REASON_EXPLICIT	0x01
#define EVT_MASK_REASON_TEMPORARY	0x02
#define EVT_MASK_REASON_EOI_PENDING	0x04
	u8 is_active;		/* Is event just being handled? */
	unsigned irq;
	unsigned int evtchn;	/* event channel */
	unsigned short cpu;	/* cpu bound */
	unsigned short eoi_cpu;	/* EOI must happen on this cpu */
	unsigned int irq_epoch;	/* If eoi_cpu valid: irq_epoch of event */
	u64 eoi_time;		/* Time in jiffies when to EOI. */
	raw_spinlock_t lock;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

	union {
		unsigned short virq;
		enum ipi_vector ipi;
		struct {
			unsigned short pirq;
			unsigned short gsi;
			unsigned char vector;
			unsigned char flags;
			uint16_t domid;
		} pirq;
	} u;
};

#define PIRQ_NEEDS_EOI	(1 << 0)
#define PIRQ_SHAREABLE	(1 << 1)
#define PIRQ_MSI_GROUP	(1 << 2)

<<<<<<< HEAD
=======
struct evtchn_loop_ctrl;

>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
struct evtchn_ops {
	unsigned (*max_channels)(void);
	unsigned (*nr_channels)(void);

	int (*setup)(struct irq_info *info);
<<<<<<< HEAD
=======
	void (*remove)(evtchn_port_t port, unsigned int cpu);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	void (*bind_to_cpu)(struct irq_info *info, unsigned cpu);

	void (*clear_pending)(unsigned port);
	void (*set_pending)(unsigned port);
	bool (*is_pending)(unsigned port);
<<<<<<< HEAD
	bool (*test_and_set_mask)(unsigned port);
	void (*mask)(unsigned port);
	void (*unmask)(unsigned port);

	void (*handle_events)(unsigned cpu);
	void (*resume)(void);
=======
	void (*mask)(unsigned port);
	void (*unmask)(unsigned port);

	void (*handle_events)(unsigned cpu, struct evtchn_loop_ctrl *ctrl);
	void (*resume)(void);

	int (*percpu_init)(unsigned int cpu);
	int (*percpu_deinit)(unsigned int cpu);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
};

extern const struct evtchn_ops *evtchn_ops;

extern int **evtchn_to_irq;
int get_evtchn_to_irq(unsigned int evtchn);
<<<<<<< HEAD
=======
void handle_irq_for_port(evtchn_port_t port, struct evtchn_loop_ctrl *ctrl);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

struct irq_info *info_for_irq(unsigned irq);
unsigned cpu_from_irq(unsigned irq);
unsigned cpu_from_evtchn(unsigned int evtchn);

static inline unsigned xen_evtchn_max_channels(void)
{
	return evtchn_ops->max_channels();
}

/*
 * Do any ABI specific setup for a bound event channel before it can
 * be unmasked and used.
 */
static inline int xen_evtchn_port_setup(struct irq_info *info)
{
	if (evtchn_ops->setup)
		return evtchn_ops->setup(info);
	return 0;
}

<<<<<<< HEAD
=======
static inline void xen_evtchn_port_remove(evtchn_port_t evtchn,
					  unsigned int cpu)
{
	if (evtchn_ops->remove)
		evtchn_ops->remove(evtchn, cpu);
}

>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
static inline void xen_evtchn_port_bind_to_cpu(struct irq_info *info,
					       unsigned cpu)
{
	evtchn_ops->bind_to_cpu(info, cpu);
}

static inline void clear_evtchn(unsigned port)
{
	evtchn_ops->clear_pending(port);
}

static inline void set_evtchn(unsigned port)
{
	evtchn_ops->set_pending(port);
}

static inline bool test_evtchn(unsigned port)
{
	return evtchn_ops->is_pending(port);
}

<<<<<<< HEAD
static inline bool test_and_set_mask(unsigned port)
{
	return evtchn_ops->test_and_set_mask(port);
}

=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
static inline void mask_evtchn(unsigned port)
{
	return evtchn_ops->mask(port);
}

static inline void unmask_evtchn(unsigned port)
{
	return evtchn_ops->unmask(port);
}

<<<<<<< HEAD
static inline void xen_evtchn_handle_events(unsigned cpu)
{
	return evtchn_ops->handle_events(cpu);
=======
static inline void xen_evtchn_handle_events(unsigned cpu,
					    struct evtchn_loop_ctrl *ctrl)
{
	return evtchn_ops->handle_events(cpu, ctrl);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}

static inline void xen_evtchn_resume(void)
{
	if (evtchn_ops->resume)
		evtchn_ops->resume();
}

void xen_evtchn_2l_init(void);
int xen_evtchn_fifo_init(void);

#endif /* #ifndef __EVENTS_INTERNAL_H__ */
