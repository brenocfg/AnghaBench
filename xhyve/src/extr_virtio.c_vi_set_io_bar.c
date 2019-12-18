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
struct virtio_softc {int /*<<< orphan*/  vs_pi; TYPE_1__* vs_vc; } ;
struct TYPE_2__ {size_t vc_cfgsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIBAR_IO ; 
 size_t VTCFG_R_CFG1 ; 
 int /*<<< orphan*/  pci_emul_alloc_bar (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t) ; 

void
vi_set_io_bar(struct virtio_softc *vs, int barnum)
{
	size_t size;

	/*
	 * ??? should we use CFG0 if MSI-X is disabled?
	 * Existing code did not...
	 */
	size = VTCFG_R_CFG1 + vs->vs_vc->vc_cfgsize;
	pci_emul_alloc_bar(vs->vs_pi, barnum, PCIBAR_IO, size);
}