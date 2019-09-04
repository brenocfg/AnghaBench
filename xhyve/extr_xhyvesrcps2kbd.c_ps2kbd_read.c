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
struct ps2kbd_softc {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int fifo_get (struct ps2kbd_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int
ps2kbd_read(struct ps2kbd_softc *sc, uint8_t *val)
{
	int retval;

	pthread_mutex_lock(&sc->mtx);
	retval = fifo_get(sc, val);
	pthread_mutex_unlock(&sc->mtx);

	return (retval);
}