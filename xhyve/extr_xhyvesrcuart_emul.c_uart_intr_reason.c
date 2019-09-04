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
struct uart_softc {int lsr; int ier; int msr; scalar_t__ thre_int_pending; } ;

/* Variables and functions */
 int IER_EMSC ; 
 int IER_ERLS ; 
 int IER_ERXRDY ; 
 int IER_ETXRDY ; 
 int IIR_MLSC ; 
 int IIR_NOPEND ; 
 int IIR_RLS ; 
 int IIR_RXTOUT ; 
 int IIR_TXRDY ; 
 int LSR_OE ; 
 int MSR_DELTA_MASK ; 
 scalar_t__ rxfifo_numchars (struct uart_softc*) ; 

__attribute__((used)) static int
uart_intr_reason(struct uart_softc *sc)
{

	if ((sc->lsr & LSR_OE) != 0 && (sc->ier & IER_ERLS) != 0)
		return (IIR_RLS);
	else if (rxfifo_numchars(sc) > 0 && (sc->ier & IER_ERXRDY) != 0)
		return (IIR_RXTOUT);
	else if (sc->thre_int_pending && (sc->ier & IER_ETXRDY) != 0)
		return (IIR_TXRDY);
	else if ((sc->msr & MSR_DELTA_MASK) != 0 && (sc->ier & IER_EMSC) != 0)
		return (IIR_MLSC);
	else
		return (IIR_NOPEND);
}