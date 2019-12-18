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
struct TYPE_9__ {int /*<<< orphan*/  seamless_active; } ;
struct TYPE_11__ {int /*<<< orphan*/  display; TYPE_1__ xwin; } ;
typedef  TYPE_3__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  XDestroyWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* sw_get_window_by_id (TYPE_3__*,unsigned long) ; 
 int /*<<< orphan*/  sw_remove_window (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  warning (char*,unsigned long) ; 

void
ui_seamless_destroy_window(RDPCLIENT * This, unsigned long id, unsigned long flags)
{
	seamless_window *sw;

	if (!This->xwin.seamless_active)
		return;

	sw = sw_get_window_by_id(This, id);
	if (!sw)
	{
		warning("ui_seamless_destroy_window: No information for window 0x%lx\n", id);
		return;
	}

	XDestroyWindow(This->display, sw->wnd);
	sw_remove_window(This, sw);
}