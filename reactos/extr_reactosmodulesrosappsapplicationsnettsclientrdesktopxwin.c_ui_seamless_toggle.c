#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  wnd; } ;
struct TYPE_7__ {int seamless_active; TYPE_5__* seamless_windows; scalar_t__ seamless_hidden; int /*<<< orphan*/  seamless_started; } ;
struct TYPE_8__ {TYPE_1__ xwin; int /*<<< orphan*/  wnd; int /*<<< orphan*/  display; int /*<<< orphan*/  seamless_rdp; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  XDestroyWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMapWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XUnmapWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seamless_send_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  sw_remove_window (TYPE_2__*,TYPE_5__*) ; 

void
ui_seamless_toggle(RDPCLIENT * This)
{
	if (!This->seamless_rdp)
		return;

	if (!This->xwin.seamless_started)
		return;

	if (This->xwin.seamless_hidden)
		return;

	if (This->xwin.seamless_active)
	{
		/* Deactivate */
		while (This->xwin.seamless_windows)
		{
			XDestroyWindow(This->display, This->xwin.seamless_windows->wnd);
			sw_remove_window(This, This->xwin.seamless_windows);
		}
		XMapWindow(This->display, This->wnd);
	}
	else
	{
		/* Activate */
		XUnmapWindow(This->display, This->wnd);
		seamless_send_sync(This);
	}

	This->xwin.seamless_active = !This->xwin.seamless_active;
}