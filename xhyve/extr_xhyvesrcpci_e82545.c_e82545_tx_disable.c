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
struct e82545_softc {int /*<<< orphan*/  esc_mtx; int /*<<< orphan*/  esc_tx_cond; scalar_t__ esc_tx_active; scalar_t__ esc_tx_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
e82545_tx_disable(struct e82545_softc *sc)
{

	sc->esc_tx_enabled = 0;
	while (sc->esc_tx_active)
		pthread_cond_wait(&sc->esc_tx_cond, &sc->esc_mtx);
}