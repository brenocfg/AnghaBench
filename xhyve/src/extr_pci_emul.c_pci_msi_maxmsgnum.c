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
struct TYPE_2__ {int maxmsgnum; scalar_t__ enabled; } ;
struct pci_devinst {TYPE_1__ pi_msi; } ;

/* Variables and functions */

__attribute__((used)) static int
pci_msi_maxmsgnum(struct pci_devinst *pi)
{
	if (pi->pi_msi.enabled)
		return (pi->pi_msi.maxmsgnum);
	else
		return (0);
}