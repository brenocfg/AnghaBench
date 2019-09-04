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
typedef  int uint64_t ;
struct pci_vtnet_softc {int vsc_features; int rx_vhdrlen; scalar_t__ rx_merge; } ;

/* Variables and functions */
 int VIRTIO_NET_F_MRG_RXBUF ; 

__attribute__((used)) static void
pci_vtnet_neg_features(void *vsc, uint64_t negotiated_features)
{
	struct pci_vtnet_softc *sc = vsc;

	sc->vsc_features = negotiated_features;

	if (!(sc->vsc_features & VIRTIO_NET_F_MRG_RXBUF)) {
		sc->rx_merge = 0;
		/* non-merge rx header is 2 bytes shorter */
		sc->rx_vhdrlen -= 2;
	}
}