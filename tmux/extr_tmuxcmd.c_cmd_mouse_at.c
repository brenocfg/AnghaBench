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
typedef  scalar_t__ u_int ;
struct window_pane {scalar_t__ xoff; scalar_t__ sx; scalar_t__ yoff; scalar_t__ sy; } ;
struct mouse_event {scalar_t__ lx; scalar_t__ ly; scalar_t__ x; scalar_t__ y; scalar_t__ statusat; } ;

/* Variables and functions */

int
cmd_mouse_at(struct window_pane *wp, struct mouse_event *m, u_int *xp,
    u_int *yp, int last)
{
	u_int	x, y;

	if (last) {
		x = m->lx;
		y = m->ly;
	} else {
		x = m->x;
		y = m->y;
	}

	if (m->statusat == 0 && y > 0)
		y--;
	else if (m->statusat > 0 && y >= (u_int)m->statusat)
		y = m->statusat - 1;

	if (x < wp->xoff || x >= wp->xoff + wp->sx)
		return (-1);
	if (y < wp->yoff || y >= wp->yoff + wp->sy)
		return (-1);

	if (xp != NULL)
		*xp = x - wp->xoff;
	if (yp != NULL)
		*yp = y - wp->yoff;
	return (0);
}