#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int table_bar; int /*<<< orphan*/ * table; } ;
struct pci_devinst {TYPE_1__ pi_msix; } ;

/* Variables and functions */

int
pci_msix_table_bar(struct pci_devinst *pi)
{

	if (pi->pi_msix.table != NULL)
		return (pi->pi_msix.table_bar);
	else
		return (-1);
}