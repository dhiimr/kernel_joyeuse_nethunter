/* SPDX-License-Identifier: GPL-2.0 */
/*
 * include/linux/arch_topology.h - arch specific cpu topology information
 */
#ifndef _LINUX_ARCH_TOPOLOGY_H_
#define _LINUX_ARCH_TOPOLOGY_H_

#include <linux/types.h>
<<<<<<< HEAD
#include <linux/percpu.h>

void topology_normalize_cpu_scale(void);
int topology_detect_flags(void);
int topology_smt_flags(void);
int topology_core_flags(void);
int topology_cpu_flags(void);
int topology_update_cpu_topology(void);
=======

void topology_normalize_cpu_scale(void);
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

struct device_node;
bool topology_parse_cpu_capacity(struct device_node *cpu_node, int cpu);

<<<<<<< HEAD
DECLARE_PER_CPU(unsigned long, cpu_scale);

struct sched_domain;
static inline
unsigned long topology_get_cpu_scale(struct sched_domain *sd, int cpu)
{
	return per_cpu(cpu_scale, cpu);
}

void topology_set_cpu_scale(unsigned int cpu, unsigned long capacity);

DECLARE_PER_CPU(unsigned long, efficiency);
static inline
unsigned long topology_get_cpu_efficiency(int cpu)
{
	return per_cpu(efficiency, cpu);
}

DECLARE_PER_CPU(unsigned long, freq_scale);

static inline
unsigned long topology_get_freq_scale(struct sched_domain *sd, int cpu)
{
	return per_cpu(freq_scale, cpu);
}

DECLARE_PER_CPU(unsigned long, max_freq_scale);

static inline
unsigned long topology_get_max_freq_scale(struct sched_domain *sd, int cpu)
{
	return per_cpu(max_freq_scale, cpu);
}

=======
struct sched_domain;
unsigned long topology_get_cpu_scale(struct sched_domain *sd, int cpu);

void topology_set_cpu_scale(unsigned int cpu, unsigned long capacity);

>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
#endif /* _LINUX_ARCH_TOPOLOGY_H_ */
