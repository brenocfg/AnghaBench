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
struct TYPE_2__ {scalar_t__ num; scalar_t__ windex; scalar_t__ rindex; } ;
struct ps2mouse_softc {int ctrlenable; int /*<<< orphan*/  mtx; TYPE_1__ fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void
ps2mouse_toggle(struct ps2mouse_softc *sc, int enable)
{
	pthread_mutex_lock(&sc->mtx);
	if (enable)
		sc->ctrlenable = 1;
	else {
		sc->ctrlenable = 0;
		sc->fifo.rindex = 0;
		sc->fifo.windex = 0;
		sc->fifo.num = 0;
	}
	pthread_mutex_unlock(&sc->mtx);
}