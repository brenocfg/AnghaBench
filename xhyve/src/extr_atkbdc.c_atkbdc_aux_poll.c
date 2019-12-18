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
struct atkbdc_softc {int status; int /*<<< orphan*/  outport; int /*<<< orphan*/  ps2mouse_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBDO_AUX_OUTFULL ; 
 int KBDS_AUX_BUFFER_FULL ; 
 int KBDS_KBD_BUFFER_FULL ; 
 int /*<<< orphan*/  atkbdc_assert_aux_intr (struct atkbdc_softc*) ; 
 scalar_t__ ps2mouse_fifocnt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
atkbdc_aux_poll(struct atkbdc_softc *sc)
{
	if (ps2mouse_fifocnt(sc->ps2mouse_sc) > 0) {
		sc->status |= KBDS_AUX_BUFFER_FULL | KBDS_KBD_BUFFER_FULL;
		sc->outport |= KBDO_AUX_OUTFULL;
		atkbdc_assert_aux_intr(sc);
	}
}