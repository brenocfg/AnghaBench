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
struct fifo {scalar_t__ num; scalar_t__ size; } ;
struct uart_softc {struct fifo rxfifo; } ;

/* Variables and functions */

__attribute__((used)) static int
rxfifo_available(struct uart_softc *sc)
{
	struct fifo *fifo;

	fifo = &sc->rxfifo;
	return (fifo->num < fifo->size);
}