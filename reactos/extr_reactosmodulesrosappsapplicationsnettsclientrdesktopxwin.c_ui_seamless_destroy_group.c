#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  wnd; TYPE_2__* group; struct TYPE_10__* next; } ;
typedef  TYPE_3__ seamless_window ;
struct TYPE_8__ {TYPE_3__* seamless_windows; int /*<<< orphan*/  seamless_active; } ;
struct TYPE_11__ {int /*<<< orphan*/  display; TYPE_1__ xwin; } ;
struct TYPE_9__ {unsigned long id; } ;
typedef  TYPE_4__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  XDestroyWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_remove_window (TYPE_4__*,TYPE_3__*) ; 

void
ui_seamless_destroy_group(RDPCLIENT * This, unsigned long id, unsigned long flags)
{
	seamless_window *sw, *sw_next;

	if (!This->xwin.seamless_active)
		return;

	for (sw = This->xwin.seamless_windows; sw; sw = sw_next)
	{
		sw_next = sw->next;

		if (sw->group->id == id)
		{
			XDestroyWindow(This->display, sw->wnd);
			sw_remove_window(This, sw);
		}
	}
}