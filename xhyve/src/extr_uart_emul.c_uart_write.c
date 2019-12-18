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
typedef  int uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  opened; } ;
struct uart_softc {int lcr; int dll; int dlh; int mcr; int thre_int_pending; int ier; int fcr; int msr; int scr; int /*<<< orphan*/  mtx; TYPE_1__ tty; int /*<<< orphan*/  lsr; } ;

/* Variables and functions */
 int FCR_DMA ; 
 int FCR_ENABLE ; 
 int FCR_RCV_RST ; 
 int FCR_RX_MASK ; 
 int FIFOSZ ; 
 int LCR_DLAB ; 
 int /*<<< orphan*/  LSR_OE ; 
 int MCR_DTR ; 
 int MCR_LOOPBACK ; 
 int MCR_OUT1 ; 
 int MCR_OUT2 ; 
 int MCR_RTS ; 
 int MSR_CTS ; 
 int MSR_DCD ; 
 int MSR_DCTS ; 
 int MSR_DDCD ; 
 int MSR_DDSR ; 
 int MSR_DELTA_MASK ; 
 int MSR_DSR ; 
 int MSR_RI ; 
 int MSR_TERI ; 
#define  REG_DATA 135 
 int REG_DLH ; 
 int REG_DLL ; 
#define  REG_FCR 134 
#define  REG_IER 133 
#define  REG_LCR 132 
#define  REG_LSR 131 
#define  REG_MCR 130 
#define  REG_MSR 129 
#define  REG_SCR 128 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxfifo_putchar (struct uart_softc*,int) ; 
 int /*<<< orphan*/  rxfifo_reset (struct uart_softc*,int) ; 
 int /*<<< orphan*/  ttywrite (TYPE_1__*,int) ; 
 int /*<<< orphan*/  uart_toggle_intr (struct uart_softc*) ; 

void
uart_write(struct uart_softc *sc, int offset, uint8_t value)
{
	int fifosz;
	uint8_t msr;

	pthread_mutex_lock(&sc->mtx);

	/*
	 * Take care of the special case DLAB accesses first
	 */
	if ((sc->lcr & LCR_DLAB) != 0) {
		if (offset == REG_DLL) {
			sc->dll = value;
			goto done;
		}

		if (offset == REG_DLH) {
			sc->dlh = value;
			goto done;
		}
	}

        switch (offset) {
	case REG_DATA:
		if (sc->mcr & MCR_LOOPBACK) {
			if (rxfifo_putchar(sc, value) != 0)
				sc->lsr |= LSR_OE;
		} else if (sc->tty.opened) {
			ttywrite(&sc->tty, value);
		} /* else drop on floor */
		sc->thre_int_pending = true;
		break;
	case REG_IER:
		/*
		 * Apply mask so that bits 4-7 are 0
		 * Also enables bits 0-3 only if they're 1
		 */
		sc->ier = value & 0x0F;
		break;
		case REG_FCR:
			/*
			 * When moving from FIFO and 16450 mode and vice versa,
			 * the FIFO contents are reset.
			 */
			if ((sc->fcr & FCR_ENABLE) ^ (value & FCR_ENABLE)) {
				fifosz = (value & FCR_ENABLE) ? FIFOSZ : 1;
				rxfifo_reset(sc, fifosz);
			}

			/*
			 * The FCR_ENABLE bit must be '1' for the programming
			 * of other FCR bits to be effective.
			 */
			if ((value & FCR_ENABLE) == 0) {
				sc->fcr = 0;
			} else {
				if ((value & FCR_RCV_RST) != 0)
					rxfifo_reset(sc, FIFOSZ);

				sc->fcr = value &
					 (FCR_ENABLE | FCR_DMA | FCR_RX_MASK);
			}
			break;
		case REG_LCR:
			sc->lcr = value;
			break;
		case REG_MCR:
			/* Apply mask so that bits 5-7 are 0 */
			sc->mcr = value & 0x1F;

			msr = 0;
			if (sc->mcr & MCR_LOOPBACK) {
				/*
				 * In the loopback mode certain bits from the
				 * MCR are reflected back into MSR
				 */
				if (sc->mcr & MCR_RTS)
					msr |= MSR_CTS;
				if (sc->mcr & MCR_DTR)
					msr |= MSR_DSR;
				if (sc->mcr & MCR_OUT1)
					msr |= MSR_RI;
				if (sc->mcr & MCR_OUT2)
					msr |= MSR_DCD;
			}

			/*
			 * Detect if there has been any change between the
			 * previous and the new value of MSR. If there is
			 * then assert the appropriate MSR delta bit.
			 */
			if ((msr & MSR_CTS) ^ (sc->msr & MSR_CTS))
				sc->msr |= MSR_DCTS;
			if ((msr & MSR_DSR) ^ (sc->msr & MSR_DSR))
				sc->msr |= MSR_DDSR;
			if ((msr & MSR_DCD) ^ (sc->msr & MSR_DCD))
				sc->msr |= MSR_DDCD;
			if ((sc->msr & MSR_RI) != 0 && (msr & MSR_RI) == 0)
				sc->msr |= MSR_TERI;

			/*
			 * Update the value of MSR while retaining the delta
			 * bits.
			 */
			sc->msr &= MSR_DELTA_MASK;
			sc->msr |= msr;
			break;
		case REG_LSR:
			/*
			 * Line status register is not meant to be written to
			 * during normal operation.
			 */
			break;
		case REG_MSR:
			/*
			 * As far as I can tell MSR is a read-only register.
			 */
			break;
		case REG_SCR:
			sc->scr = value;
			break;
		default:
			break;
	}

done:
	uart_toggle_intr(sc);
	pthread_mutex_unlock(&sc->mtx);
}