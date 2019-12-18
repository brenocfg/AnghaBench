#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct window_pane {scalar_t__ xoff; scalar_t__ yoff; TYPE_3__* screen; } ;
struct window {scalar_t__ sx; scalar_t__ sy; struct window_pane* active; } ;
struct tty {scalar_t__ sx; scalar_t__ sy; struct client* client; } ;
struct client {scalar_t__ pan_ox; scalar_t__ pan_oy; struct window* pan_window; TYPE_2__* session; } ;
struct TYPE_6__ {int mode; scalar_t__ cx; scalar_t__ cy; } ;
struct TYPE_5__ {TYPE_1__* curw; } ;
struct TYPE_4__ {struct window* window; } ;

/* Variables and functions */
 int MODE_CURSOR ; 
 scalar_t__ status_line_size (struct client*) ; 

__attribute__((used)) static int
tty_window_offset1(struct tty *tty, u_int *ox, u_int *oy, u_int *sx, u_int *sy)
{
	struct client		*c = tty->client;
	struct window		*w = c->session->curw->window;
	struct window_pane	*wp = w->active;
	u_int			 cx, cy, lines;

	lines = status_line_size(c);

	if (tty->sx >= w->sx && tty->sy - lines >= w->sy) {
		*ox = 0;
		*oy = 0;
		*sx = w->sx;
		*sy = w->sy;

		c->pan_window = NULL;
		return (0);
	}

	*sx = tty->sx;
	*sy = tty->sy - lines;

	if (c->pan_window == w) {
		if (*sx >= w->sx)
			c->pan_ox = 0;
		else if (c->pan_ox + *sx > w->sx)
			c->pan_ox = w->sx - *sx;
		*ox = c->pan_ox;
		if (*sy >= w->sy)
			c->pan_oy = 0;
		else if (c->pan_oy + *sy > w->sy)
			c->pan_oy = w->sy - *sy;
		*oy = c->pan_oy;
		return (1);
	}

	if (~wp->screen->mode & MODE_CURSOR) {
		*ox = 0;
		*oy = 0;
	} else {
		cx = wp->xoff + wp->screen->cx;
		cy = wp->yoff + wp->screen->cy;

		if (cx < *sx)
			*ox = 0;
		else if (cx > w->sx - *sx)
			*ox = w->sx - *sx;
		else
			*ox = cx - *sx / 2;

		if (cy < *sy)
			*oy = 0;
		else if (cy > w->sy - *sy)
			*oy = w->sy - *sy;
		else
			*oy = cy - *sy / 2;
	}

	c->pan_window = NULL;
	return (1);
}