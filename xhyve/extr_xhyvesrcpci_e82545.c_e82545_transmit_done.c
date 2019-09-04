#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int data; } ;
struct TYPE_6__ {TYPE_2__ upper; TYPE_1__ lower; } ;
union e1000_tx_udesc {TYPE_3__ td; } ;
typedef  int uint16_t ;
struct e82545_softc {union e1000_tx_udesc* esc_txdesc; } ;

/* Variables and functions */
 int E1000_TXD_CMD_RS ; 
 int /*<<< orphan*/  E1000_TXD_STAT_DD ; 

__attribute__((used)) static void
e82545_transmit_done(struct e82545_softc *sc, uint16_t head, uint16_t tail,
    uint16_t dsize, int *tdwb)
{
	union e1000_tx_udesc *dsc;

	for ( ; head != tail; head = (head + 1) % dsize) {
		dsc = &sc->esc_txdesc[head];
		if (dsc->td.lower.data & E1000_TXD_CMD_RS) {
			dsc->td.upper.data |= E1000_TXD_STAT_DD;
			*tdwb = 1;
		}
	}
}