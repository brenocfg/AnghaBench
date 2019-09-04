#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct pci_devinst {int dummy; } ;
typedef  enum pcibar_type { ____Placeholder_pcibar_type } pcibar_type ;

/* Variables and functions */
 int pci_emul_alloc_pbar (struct pci_devinst*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
pci_emul_alloc_bar(struct pci_devinst *pdi, int idx, enum pcibar_type type,
		   uint64_t size)
{

	return (pci_emul_alloc_pbar(pdi, idx, 0, type, size));
}