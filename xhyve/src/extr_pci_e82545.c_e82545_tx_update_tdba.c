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
struct e82545_softc {int esc_tdba; int esc_TDBAL; int /*<<< orphan*/  esc_TDLEN; int /*<<< orphan*/  esc_txdesc; scalar_t__ esc_TDBAH; } ;

/* Variables and functions */
 int /*<<< orphan*/  paddr_guest2host (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
e82545_tx_update_tdba(struct e82545_softc *sc)
{

	/* XXX verify desc base/len within phys mem range */
	sc->esc_tdba = (uint64_t)sc->esc_TDBAH << 32 | sc->esc_TDBAL;

	/* Cache host mapping of guest descriptor array */
	sc->esc_txdesc = paddr_guest2host(sc->esc_tdba, sc->esc_TDLEN);
}