#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  wnd; } ;
struct TYPE_6__ {TYPE_5__* seamless_windows; int /*<<< orphan*/  seamless_active; } ;
struct TYPE_7__ {TYPE_1__ xwin; int /*<<< orphan*/  display; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  XDestroyWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_remove_window (TYPE_2__*,TYPE_5__*) ; 

void
ui_seamless_syncbegin(RDPCLIENT * This, unsigned long flags)
{
	if (!This->xwin.seamless_active)
		return;

	/* Destroy all seamless windows */
	while (This->xwin.seamless_windows)
	{
		XDestroyWindow(This->display, This->xwin.seamless_windows->wnd);
		sw_remove_window(This, This->xwin.seamless_windows);
	}
}