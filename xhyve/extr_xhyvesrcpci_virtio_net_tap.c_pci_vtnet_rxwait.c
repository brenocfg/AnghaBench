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
struct pci_vtnet_softc {int /*<<< orphan*/  rx_mtx; scalar_t__ rx_in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void
pci_vtnet_rxwait(struct pci_vtnet_softc *sc)
{

	pthread_mutex_lock(&sc->rx_mtx);
	while (sc->rx_in_progress) {
		pthread_mutex_unlock(&sc->rx_mtx);
		usleep(10000);
		pthread_mutex_lock(&sc->rx_mtx);
	}
	pthread_mutex_unlock(&sc->rx_mtx);
}