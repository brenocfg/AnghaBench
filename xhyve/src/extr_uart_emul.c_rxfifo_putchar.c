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
struct TYPE_2__ {scalar_t__ opened; } ;
struct fifo {int num; int size; size_t windex; int /*<<< orphan*/ * buf; } ;
struct uart_softc {int /*<<< orphan*/  mev; TYPE_1__ tty; struct fifo rxfifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int mevent_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxfifo_available (struct uart_softc*) ; 

__attribute__((used)) static int
rxfifo_putchar(struct uart_softc *sc, uint8_t ch)
{
	struct fifo *fifo;
	int error;

	fifo = &sc->rxfifo;

	if (fifo->num < fifo->size) {
		fifo->buf[fifo->windex] = ch;
		fifo->windex = (fifo->windex + 1) % fifo->size;
		fifo->num++;
		if (!rxfifo_available(sc)) {
			if (sc->tty.opened) {
				/*
				 * Disable mevent callback if the FIFO is full.
				 */
				error = mevent_disable(sc->mev);
				assert(error == 0);
			}
		}
		return (0);
	} else
		return (-1);
}