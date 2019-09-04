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
struct ps2mouse_softc {int cur_x; int cur_y; int /*<<< orphan*/  delta_y; int /*<<< orphan*/  delta_x; } ;

/* Variables and functions */

__attribute__((used)) static void
movement_update(struct ps2mouse_softc *sc, int x, int y)
{
	sc->delta_x += x - sc->cur_x;
	sc->delta_y += sc->cur_y - y;
	sc->cur_x = x;
	sc->cur_y = y;
}