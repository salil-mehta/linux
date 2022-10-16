// SPDX-License-Identifier: GPL-2.0
#include <linux/cpu.h>
#include <linux/cpumask.h>
#include <linux/init.h>
#include <linux/node.h>
#include <linux/nodemask.h>
#include <linux/percpu.h>
#include <asm/bootinfo.h>

#ifdef CONFIG_HOTPLUG_CPU
int arch_register_cpu(int cpu)
{
	int ret;
	struct cpu *c = &per_cpu(cpu_devices, cpu);

	c->hotpluggable = !!cpu;
	ret = register_cpu(c, cpu);
	if (ret < 0)
		pr_warn("register_cpu %d failed (%d)\n", cpu, ret);

	return ret;
}
EXPORT_SYMBOL(arch_register_cpu);

void arch_unregister_cpu(int cpu)
{
	struct cpu *c = &per_cpu(cpu_devices, cpu);

	c->hotpluggable = 0;
	unregister_cpu(c);
}
EXPORT_SYMBOL(arch_unregister_cpu);
#endif

subsys_initcall(topology_init);
