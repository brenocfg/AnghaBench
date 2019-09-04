#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ wnd; scalar_t__ behind; scalar_t__ id; } ;
typedef  TYPE_2__ seamless_window ;
typedef  scalar_t__ Window ;
struct TYPE_11__ {int /*<<< orphan*/  screen; } ;
struct TYPE_13__ {TYPE_1__ xwin; int /*<<< orphan*/  display; } ;
typedef  int /*<<< orphan*/  Status ;
typedef  TYPE_3__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  RootWindowOfScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFree (scalar_t__*) ; 
 int /*<<< orphan*/  XQueryTree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__**,unsigned int*) ; 
 int /*<<< orphan*/  seamless_send_zchange (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* sw_get_window_by_wnd (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  sw_restack_window (TYPE_3__*,TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static void
sw_handle_restack(RDPCLIENT * This, seamless_window * sw)
{
	Status status;
	Window root, parent, *children;
	unsigned int nchildren, i;
	seamless_window *sw_below;

	status = XQueryTree(This->display, RootWindowOfScreen(This->xwin.screen),
			    &root, &parent, &children, &nchildren);
	if (!status || !nchildren)
		return;

	sw_below = NULL;

	i = 0;
	while (children[i] != sw->wnd)
	{
		i++;
		if (i >= nchildren)
			goto end;
	}

	for (i++; i < nchildren; i++)
	{
		sw_below = sw_get_window_by_wnd(This, children[i]);
		if (sw_below)
			break;
	}

	if (!sw_below && !sw->behind)
		goto end;
	if (sw_below && (sw_below->id == sw->behind))
		goto end;

	if (sw_below)
	{
		seamless_send_zchange(This, sw->id, sw_below->id, 0);
		sw_restack_window(This, sw, sw_below->id);
	}
	else
	{
		seamless_send_zchange(This, sw->id, 0, 0);
		sw_restack_window(This, sw, 0);
	}

      end:
	XFree(children);
}