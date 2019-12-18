#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  wnd; } ;
struct TYPE_8__ {int /*<<< orphan*/  gc; int /*<<< orphan*/  backstore; int /*<<< orphan*/  mod_map; int /*<<< orphan*/ * null_cursor; int /*<<< orphan*/ * IM; TYPE_7__* seamless_windows; } ;
struct TYPE_9__ {int /*<<< orphan*/ * display; TYPE_1__ xwin; scalar_t__ ownbackstore; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XCloseIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDestroyWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreeGC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreeModifiermap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreePixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_remove_window (TYPE_2__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ui_destroy_cursor (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xclip_deinit (TYPE_2__*) ; 

void
ui_deinit(RDPCLIENT * This)
{
	while (This->xwin.seamless_windows)
	{
		XDestroyWindow(This->display, This->xwin.seamless_windows->wnd);
		sw_remove_window(This, This->xwin.seamless_windows);
	}

	xclip_deinit(This);

	if (This->xwin.IM != NULL)
		XCloseIM(This->xwin.IM);

	if (This->xwin.null_cursor != NULL)
		ui_destroy_cursor(This, This->xwin.null_cursor);

	XFreeModifiermap(This->xwin.mod_map);

	if (This->ownbackstore)
		XFreePixmap(This->display, This->xwin.backstore);

	XFreeGC(This->display, This->xwin.gc);
	XCloseDisplay(This->display);
	This->display = NULL;
}