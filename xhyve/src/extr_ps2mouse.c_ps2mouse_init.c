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
struct ps2mouse_softc {int /*<<< orphan*/  mtx; struct atkbdc_softc* atkbdc_sc; } ;
struct atkbdc_softc {int dummy; } ;

/* Variables and functions */
 struct ps2mouse_softc* calloc (int,int) ; 
 int /*<<< orphan*/  console_ptr_register (int /*<<< orphan*/ ,struct ps2mouse_softc*,int) ; 
 int /*<<< orphan*/  fifo_init (struct ps2mouse_softc*) ; 
 int /*<<< orphan*/  ps2mouse_event ; 
 int /*<<< orphan*/  ps2mouse_reset (struct ps2mouse_softc*) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

struct ps2mouse_softc *
ps2mouse_init(struct atkbdc_softc *atkbdc_sc)
{
	struct ps2mouse_softc *sc;

	sc = calloc(1, sizeof (struct ps2mouse_softc));
	pthread_mutex_init(&sc->mtx, NULL);
	fifo_init(sc);
	sc->atkbdc_sc = atkbdc_sc;

	pthread_mutex_lock(&sc->mtx);
	ps2mouse_reset(sc);
	pthread_mutex_unlock(&sc->mtx);

	console_ptr_register(ps2mouse_event, sc, 1);

	return (sc);
}