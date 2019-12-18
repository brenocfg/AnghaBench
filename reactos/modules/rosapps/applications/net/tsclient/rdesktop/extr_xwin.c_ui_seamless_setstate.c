#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {unsigned int state; int /*<<< orphan*/  wnd; } ;
typedef  TYPE_2__ seamless_window ;
struct TYPE_14__ {int /*<<< orphan*/  initial_state; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ XWMHints ;
struct TYPE_12__ {int /*<<< orphan*/  seamless_active; } ;
struct TYPE_15__ {int /*<<< orphan*/  display; TYPE_1__ xwin; } ;
typedef  TYPE_4__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IconicState ; 
#define  SEAMLESSRDP_MAXIMIZED 130 
#define  SEAMLESSRDP_MINIMIZED 129 
#define  SEAMLESSRDP_NORMAL 128 
 unsigned int SEAMLESSRDP_NOTYETMAPPED ; 
 int /*<<< orphan*/  StateHint ; 
 int /*<<< orphan*/  XFree (TYPE_3__*) ; 
 TYPE_3__* XGetWMHints (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XIconifyWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMapWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetWMHints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ewmh_change_state (TYPE_4__*,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_2__* sw_get_window_by_id (TYPE_4__*,unsigned long) ; 
 int /*<<< orphan*/  warning (char*,unsigned int) ; 

void
ui_seamless_setstate(RDPCLIENT * This, unsigned long id, unsigned int state, unsigned long flags)
{
	seamless_window *sw;

	if (!This->xwin.seamless_active)
		return;

	sw = sw_get_window_by_id(This, id);
	if (!sw)
	{
		warning("ui_seamless_setstate: No information for window 0x%lx\n", id);
		return;
	}

	switch (state)
	{
		case SEAMLESSRDP_NORMAL:
		case SEAMLESSRDP_MAXIMIZED:
			ewmh_change_state(This, sw->wnd, state);
			XMapWindow(This->display, sw->wnd);
			break;
		case SEAMLESSRDP_MINIMIZED:
			/* EWMH says: "if an Application asks to toggle _NET_WM_STATE_HIDDEN
			   the Window Manager should probably just ignore the request, since
			   _NET_WM_STATE_HIDDEN is a function of some other aspect of the window
			   such as minimization, rather than an independent state." Besides,
			   XIconifyWindow is easier. */
			if (sw->state == SEAMLESSRDP_NOTYETMAPPED)
			{
				XWMHints *hints;
				hints = XGetWMHints(This->display, sw->wnd);
				if (hints)
				{
					hints->flags |= StateHint;
					hints->initial_state = IconicState;
					XSetWMHints(This->display, sw->wnd, hints);
					XFree(hints);
				}
				XMapWindow(This->display, sw->wnd);
			}
			else
				XIconifyWindow(This->display, sw->wnd, DefaultScreen(This->display));
			break;
		default:
			warning("SeamlessRDP: Invalid state %d\n", state);
			break;
	}

	sw->state = state;
}