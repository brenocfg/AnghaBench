#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int xoffset; int yoffset; int width; int height; int state; int /*<<< orphan*/  wnd; scalar_t__ outstanding_position; } ;
typedef  TYPE_2__ seamless_window ;
struct TYPE_7__ {int /*<<< orphan*/  seamless_active; } ;
struct TYPE_9__ {int /*<<< orphan*/  display; TYPE_1__ xwin; } ;
typedef  TYPE_3__ RDPCLIENT ;

/* Variables and functions */
#define  SEAMLESSRDP_MAXIMIZED 129 
#define  SEAMLESSRDP_MINIMIZED 128 
 int /*<<< orphan*/  XMoveResizeWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 TYPE_2__* sw_get_window_by_id (TYPE_3__*,unsigned long) ; 
 int /*<<< orphan*/  warning (char*,unsigned long) ; 

void
ui_seamless_move_window(RDPCLIENT * This, unsigned long id, int x, int y, int width, int height, unsigned long flags)
{
	seamless_window *sw;

	if (!This->xwin.seamless_active)
		return;

	sw = sw_get_window_by_id(This, id);
	if (!sw)
	{
		warning("ui_seamless_move_window: No information for window 0x%lx\n", id);
		return;
	}

	/* We ignore server updates until it has handled our request. */
	if (sw->outstanding_position)
		return;

	if (!width || !height)
		/* X11 windows must be at least 1x1 */
		return;

	sw->xoffset = x;
	sw->yoffset = y;
	sw->width = width;
	sw->height = height;

	/* If we move the window in a maximized state, then KDE won't
	   accept restoration */
	switch (sw->state)
	{
		case SEAMLESSRDP_MINIMIZED:
		case SEAMLESSRDP_MAXIMIZED:
			return;
	}

	/* FIXME: Perhaps use ewmh_net_moveresize_window instead */
	XMoveResizeWindow(This->display, sw->wnd, sw->xoffset, sw->yoffset, sw->width, sw->height);
}