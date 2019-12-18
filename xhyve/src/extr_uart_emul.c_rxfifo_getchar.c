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
struct TYPE_2__ {scalar_t__ opened; } ;
struct fifo {scalar_t__ num; int* buf; size_t rindex; int size; } ;
struct uart_softc {int /*<<< orphan*/  mev; TYPE_1__ tty; struct fifo rxfifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int mevent_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxfifo_available (struct uart_softc*) ; 

__attribute__((used)) static int
rxfifo_getchar(struct uart_softc *sc)
{
	struct fifo *fifo;
	int c, error, wasfull;

	wasfull = 0;
	fifo = &sc->rxfifo;
	if (fifo->num > 0) {
		if (!rxfifo_available(sc))
			wasfull = 1;
		c = fifo->buf[fifo->rindex];
		fifo->rindex = (fifo->rindex + 1) % fifo->size;
		fifo->num--;
		if (wasfull) {
			if (sc->tty.opened) {
				error = mevent_enable(sc->mev);
				assert(error == 0);
			}
		}
		return (c);
	} else
		return (-1);
}