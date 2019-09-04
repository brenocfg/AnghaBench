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
typedef  int /*<<< orphan*/  uint8_t ;
struct fifo {scalar_t__ num; size_t rindex; int size; int /*<<< orphan*/ * buf; } ;
struct ps2kbd_softc {struct fifo fifo; } ;

/* Variables and functions */

__attribute__((used)) static int
fifo_get(struct ps2kbd_softc *sc, uint8_t *val)
{
	struct fifo *fifo;

	fifo = &sc->fifo;
	if (fifo->num > 0) {
		*val = fifo->buf[fifo->rindex];
		fifo->rindex = (fifo->rindex + 1) % fifo->size;
		fifo->num--;
		return (0);
	}

	return (-1);
}