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
typedef  int uint32_t ;
struct e82545_softc {int esc_RCTL; int esc_rx_enabled; int esc_rx_loopback; int /*<<< orphan*/ * esc_rxdesc; scalar_t__ esc_rdba; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,char*,int,int) ; 
 int E1000_RCTL_EN ; 
 int E1000_RCTL_LBM_TCVR ; 
 int /*<<< orphan*/  e82545_rx_disable (struct e82545_softc*) ; 
 int /*<<< orphan*/  e82545_rx_enable (struct e82545_softc*) ; 
 int /*<<< orphan*/  e82545_rx_update_rdba (struct e82545_softc*) ; 

__attribute__((used)) static void
e82545_rx_ctl(struct e82545_softc *sc, uint32_t val)
{
	int on;

	on = ((val & E1000_RCTL_EN) == E1000_RCTL_EN);

	/* Save RCTL after stripping reserved bits 31:27,24,21,14,11:10,0 */
	sc->esc_RCTL = val & ~0xF9204c01;

	DPRINTF("rx_ctl - %s RCTL %x, val %x\n",
		on ? "on" : "off", sc->esc_RCTL, val);

	/* state change requested */
	if (on != sc->esc_rx_enabled) {
		if (on) {
			/* Catch disallowed/unimplemented settings */
			//assert(!(val & E1000_RCTL_LBM_TCVR));

			if (sc->esc_RCTL & E1000_RCTL_LBM_TCVR) {
				sc->esc_rx_loopback = 1;
			} else {
				sc->esc_rx_loopback = 0;
			}

			e82545_rx_update_rdba(sc);
			e82545_rx_enable(sc);
		} else {
			e82545_rx_disable(sc);
			sc->esc_rx_loopback = 0;
			sc->esc_rdba = 0;
			sc->esc_rxdesc = NULL;
		}
	}
}