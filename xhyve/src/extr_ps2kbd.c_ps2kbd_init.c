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
struct ps2kbd_softc {struct atkbdc_softc* atkbdc_sc; int /*<<< orphan*/  mtx; } ;
struct atkbdc_softc {int dummy; } ;

/* Variables and functions */
 struct ps2kbd_softc* calloc (int,int) ; 
 int /*<<< orphan*/  console_kbd_register (int /*<<< orphan*/ ,struct ps2kbd_softc*,int) ; 
 int /*<<< orphan*/  fifo_init (struct ps2kbd_softc*) ; 
 int /*<<< orphan*/  ps2kbd_event ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct ps2kbd_softc *
ps2kbd_init(struct atkbdc_softc *atkbdc_sc)
{
	struct ps2kbd_softc *sc;

	sc = calloc(1, sizeof (struct ps2kbd_softc));
	pthread_mutex_init(&sc->mtx, NULL);
	fifo_init(sc);
	sc->atkbdc_sc = atkbdc_sc;

	console_kbd_register(ps2kbd_event, sc, 1);

	return (sc);
}