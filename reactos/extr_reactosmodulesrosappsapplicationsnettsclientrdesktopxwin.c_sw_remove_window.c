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
struct TYPE_8__ {scalar_t__ refcnt; struct TYPE_8__* next; struct TYPE_8__* position_timer; struct TYPE_8__* group; int /*<<< orphan*/  wnd; } ;
typedef  TYPE_2__ seamless_window ;
struct TYPE_7__ {TYPE_2__* seamless_windows; } ;
struct TYPE_9__ {int /*<<< orphan*/  display; TYPE_1__ xwin; } ;
typedef  TYPE_3__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  XDestroyWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (TYPE_2__*) ; 

__attribute__((used)) static void
sw_remove_window(RDPCLIENT * This, seamless_window * win)
{
	seamless_window *sw, **prevnext = &This->xwin.seamless_windows;
	for (sw = This->xwin.seamless_windows; sw; sw = sw->next)
	{
		if (sw == win)
		{
			*prevnext = sw->next;
			sw->group->refcnt--;
			if (sw->group->refcnt == 0)
			{
				XDestroyWindow(This->display, sw->group->wnd);
				xfree(sw->group);
			}
			xfree(sw->position_timer);
			xfree(sw);
			return;
		}
		prevnext = &sw->next;
	}
	return;
}