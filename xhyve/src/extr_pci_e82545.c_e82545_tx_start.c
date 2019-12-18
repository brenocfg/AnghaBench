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
struct e82545_softc {scalar_t__ esc_tx_active; int /*<<< orphan*/  esc_tx_cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
e82545_tx_start(struct e82545_softc *sc)
{

	if (sc->esc_tx_active == 0)
		pthread_cond_signal(&sc->esc_tx_cond);
}