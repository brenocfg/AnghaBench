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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int fd; } ;
struct uart_softc {int mcr; int /*<<< orphan*/  mtx; TYPE_1__ tty; } ;
typedef  enum ev_type { ____Placeholder_ev_type } ev_type ;

/* Variables and functions */
 int EVF_READ ; 
 int MCR_LOOPBACK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rxfifo_available (struct uart_softc*) ; 
 int /*<<< orphan*/  rxfifo_putchar (struct uart_softc*,int /*<<< orphan*/ ) ; 
 int ttyread (TYPE_1__*) ; 
 int /*<<< orphan*/  uart_toggle_intr (struct uart_softc*) ; 

__attribute__((used)) static void
uart_drain(int fd, enum ev_type ev, void *arg)
{
	struct uart_softc *sc;
	int ch;

	sc = arg;

	assert(fd == sc->tty.fd);
	assert(ev == EVF_READ);

	/*
	 * This routine is called in the context of the mevent thread
	 * to take out the softc lock to protect against concurrent
	 * access from a vCPU i/o exit
	 */
	pthread_mutex_lock(&sc->mtx);

	if ((sc->mcr & MCR_LOOPBACK) != 0) {
		(void) ttyread(&sc->tty);
	} else {
		while (rxfifo_available(sc) &&
		       ((ch = ttyread(&sc->tty)) != -1)) {
			rxfifo_putchar(sc, ((uint8_t) ch));
		}
		uart_toggle_intr(sc);
	}

	pthread_mutex_unlock(&sc->mtx);
}