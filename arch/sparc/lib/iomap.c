// SPDX-License-Identifier: GPL-2.0
/*
 * Implement the sparc iomap interfaces
 */
#include <linux/pci.h>
#include <linux/module.h>
#include <asm/io.h>

/* Create a virtual mapping cookie for an IO port range */
void __iomem *ioport_map(unsigned long port, unsigned int nr)
{
	return (void __iomem *) (unsigned long) port;
}

void ioport_unmap(void __iomem *addr)
{
	/* Nothing to do */
}
EXPORT_SYMBOL(ioport_map);
EXPORT_SYMBOL(ioport_unmap);

<<<<<<< HEAD
=======
#ifdef CONFIG_PCI
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
void pci_iounmap(struct pci_dev *dev, void __iomem * addr)
{
	/* nothing to do */
}
EXPORT_SYMBOL(pci_iounmap);
<<<<<<< HEAD
=======
#endif
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
