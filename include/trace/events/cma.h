/* SPDX-License-Identifier: GPL-2.0 */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM cma

#if !defined(_TRACE_CMA_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_CMA_H

#include <linux/types.h>
#include <linux/tracepoint.h>

<<<<<<< HEAD
DECLARE_EVENT_CLASS(cma_alloc_class,
=======
TRACE_EVENT(cma_alloc,
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

	TP_PROTO(unsigned long pfn, const struct page *page,
		 unsigned int count, unsigned int align),

	TP_ARGS(pfn, page, count, align),

	TP_STRUCT__entry(
		__field(unsigned long, pfn)
		__field(const struct page *, page)
		__field(unsigned int, count)
		__field(unsigned int, align)
	),

	TP_fast_assign(
		__entry->pfn = pfn;
		__entry->page = page;
		__entry->count = count;
		__entry->align = align;
	),

	TP_printk("pfn=%lx page=%p count=%u align=%u",
		  __entry->pfn,
		  __entry->page,
		  __entry->count,
		  __entry->align)
);

TRACE_EVENT(cma_release,

	TP_PROTO(unsigned long pfn, const struct page *page,
		 unsigned int count),

	TP_ARGS(pfn, page, count),

	TP_STRUCT__entry(
		__field(unsigned long, pfn)
		__field(const struct page *, page)
		__field(unsigned int, count)
	),

	TP_fast_assign(
		__entry->pfn = pfn;
		__entry->page = page;
		__entry->count = count;
	),

	TP_printk("pfn=%lx page=%p count=%u",
		  __entry->pfn,
		  __entry->page,
		  __entry->count)
);

<<<<<<< HEAD
TRACE_EVENT(cma_alloc_start,

	TP_PROTO(unsigned int count, unsigned int align),

	TP_ARGS(count, align),

	TP_STRUCT__entry(
		__field(unsigned int, count)
		__field(unsigned int, align)
	),

	TP_fast_assign(
		__entry->count = count;
		__entry->align = align;
	),

	TP_printk("count=%u align=%u",
		  __entry->count,
		  __entry->align)
);

DEFINE_EVENT(cma_alloc_class, cma_alloc,

	TP_PROTO(unsigned long pfn, const struct page *page,
		 unsigned int count, unsigned int align),

	TP_ARGS(pfn, page, count, align)
);

DEFINE_EVENT(cma_alloc_class, cma_alloc_busy_retry,

	TP_PROTO(unsigned long pfn, const struct page *page,
		 unsigned int count, unsigned int align),

	TP_ARGS(pfn, page, count, align)
);


=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
#endif /* _TRACE_CMA_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
