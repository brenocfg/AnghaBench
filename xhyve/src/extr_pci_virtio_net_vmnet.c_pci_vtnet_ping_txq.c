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
struct vqueue_info {TYPE_1__* vq_used; } ;
struct pci_vtnet_softc {scalar_t__ tx_in_progress; int /*<<< orphan*/  tx_mtx; int /*<<< orphan*/  tx_cond; } ;
struct TYPE_2__ {int /*<<< orphan*/  vu_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VRING_USED_F_NO_NOTIFY ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vq_has_descs (struct vqueue_info*) ; 

__attribute__((used)) static void
pci_vtnet_ping_txq(void *vsc, struct vqueue_info *vq)
{
	struct pci_vtnet_softc *sc = vsc;

	/*
	 * Any ring entries to process?
	 */
	if (!vq_has_descs(vq))
		return;

	/* Signal the tx thread for processing */
	pthread_mutex_lock(&sc->tx_mtx);
	vq->vq_used->vu_flags |= VRING_USED_F_NO_NOTIFY;
	if (sc->tx_in_progress == 0)
		pthread_cond_signal(&sc->tx_cond);
	pthread_mutex_unlock(&sc->tx_mtx);
}