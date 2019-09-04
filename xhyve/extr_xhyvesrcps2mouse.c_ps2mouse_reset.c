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
struct ps2mouse_softc {int resolution; int sampling_rate; scalar_t__ delta_y; scalar_t__ delta_x; scalar_t__ cur_y; scalar_t__ cur_x; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS2M_STS_ENABLE_DEV ; 
 int /*<<< orphan*/  fifo_reset (struct ps2mouse_softc*) ; 
 int /*<<< orphan*/  movement_reset (struct ps2mouse_softc*) ; 

__attribute__((used)) static void
ps2mouse_reset(struct ps2mouse_softc *sc)
{
	fifo_reset(sc);
	movement_reset(sc);
	sc->status = PS2M_STS_ENABLE_DEV;
	sc->resolution = 4;
	sc->sampling_rate = 100;

	sc->cur_x = 0;
	sc->cur_y = 0;
	sc->delta_x = 0;
	sc->delta_y = 0;
}