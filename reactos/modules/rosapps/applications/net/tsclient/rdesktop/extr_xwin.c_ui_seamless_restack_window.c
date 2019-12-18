#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  wnd; } ;
typedef  TYPE_2__ seamless_window ;
typedef  int /*<<< orphan*/  Window ;
struct TYPE_9__ {int /*<<< orphan*/  seamless_active; } ;
struct TYPE_11__ {int /*<<< orphan*/  display; TYPE_1__ xwin; } ;
typedef  TYPE_3__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  XRaiseWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XRestackWindows (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* sw_get_window_by_id (TYPE_3__*,unsigned long) ; 
 int /*<<< orphan*/  sw_restack_window (TYPE_3__*,TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  warning (char*,unsigned long) ; 

void
ui_seamless_restack_window(RDPCLIENT * This, unsigned long id, unsigned long behind, unsigned long flags)
{
	seamless_window *sw;

	if (!This->xwin.seamless_active)
		return;

	sw = sw_get_window_by_id(This, id);
	if (!sw)
	{
		warning("ui_seamless_restack_window: No information for window 0x%lx\n", id);
		return;
	}

	if (behind)
	{
		seamless_window *sw_behind;
		Window wnds[2];

		sw_behind = sw_get_window_by_id(This, behind);
		if (!sw_behind)
		{
			warning("ui_seamless_restack_window: No information for window 0x%lx\n",
				behind);
			return;
		}

		wnds[1] = sw_behind->wnd;
		wnds[0] = sw->wnd;

		XRestackWindows(This->display, wnds, 2);
	}
	else
	{
		XRaiseWindow(This->display, sw->wnd);
	}

	sw_restack_window(This, sw, behind);
}