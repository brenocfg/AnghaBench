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
struct ps2mouse_softc {scalar_t__ delta_y; scalar_t__ delta_x; } ;

/* Variables and functions */

__attribute__((used)) static void
movement_reset(struct ps2mouse_softc *sc)
{
	sc->delta_x = 0;
	sc->delta_y = 0;
}