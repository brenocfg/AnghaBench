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
struct virtio_softc {int /*<<< orphan*/  vs_pi; int /*<<< orphan*/  vs_flags; TYPE_1__* vs_vc; } ;
struct TYPE_2__ {int vc_nvq; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_USE_MSIX ; 
 int /*<<< orphan*/  VS_LOCK (struct virtio_softc*) ; 
 int /*<<< orphan*/  VS_UNLOCK (struct virtio_softc*) ; 
 int /*<<< orphan*/  pci_emul_add_msicap (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_emul_add_msixcap (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_lintr_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vi_reset_dev (struct virtio_softc*) ; 

int
vi_intr_init(struct virtio_softc *vs, int barnum, int use_msix)
{
	int nvec;

	if (use_msix) {
		vs->vs_flags |= VIRTIO_USE_MSIX;
		VS_LOCK(vs);
		vi_reset_dev(vs); /* set all vectors to NO_VECTOR */
		VS_UNLOCK(vs);
		nvec = vs->vs_vc->vc_nvq + 1;
		if (pci_emul_add_msixcap(vs->vs_pi, nvec, barnum))
			return (1);
	} else
		vs->vs_flags &= ~VIRTIO_USE_MSIX;

	/* Only 1 MSI vector for bhyve */
	pci_emul_add_msicap(vs->vs_pi, 1);

	/* Legacy interrupts are mandatory for virtio devices */
	pci_lintr_request(vs->vs_pi);

	return (0);
}