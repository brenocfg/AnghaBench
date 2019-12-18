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
struct pci_vtblk_softc {int /*<<< orphan*/  vsc_mtx; } ;
struct pci_vtblk_ioreq {struct pci_vtblk_softc* io_sc; } ;
struct blockif_req {struct pci_vtblk_ioreq* br_param; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_vtblk_done_locked (struct blockif_req*,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pci_vtblk_done(struct blockif_req *br, int err) {
	struct pci_vtblk_ioreq *io = br->br_param;
	struct pci_vtblk_softc *sc = io->io_sc;

	pthread_mutex_lock(&sc->vsc_mtx);
	pci_vtblk_done_locked(br, err);
	pthread_mutex_unlock(&sc->vsc_mtx);
}