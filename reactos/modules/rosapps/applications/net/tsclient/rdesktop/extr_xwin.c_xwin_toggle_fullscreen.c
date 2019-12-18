#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  gc; int /*<<< orphan*/  current_cursor; int /*<<< orphan*/  depth; scalar_t__ seamless_active; } ;
struct TYPE_8__ {int fullscreen; int /*<<< orphan*/  display; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__ xwin; int /*<<< orphan*/  wnd; int /*<<< orphan*/  ownbackstore; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  Pixmap ;

/* Variables and functions */
 int /*<<< orphan*/  XCopyArea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCreatePixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDefineCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreePixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_create_window (TYPE_2__*) ; 
 int /*<<< orphan*/  ui_destroy_window (TYPE_2__*) ; 
 int /*<<< orphan*/  ui_seamless_toggle (TYPE_2__*) ; 

void
xwin_toggle_fullscreen(RDPCLIENT * This)
{
	Pixmap contents = 0;

	if (This->xwin.seamless_active)
		/* Turn off SeamlessRDP mode */
		ui_seamless_toggle(This);

	if (!This->ownbackstore)
	{
		/* need to save contents of window */
		contents = XCreatePixmap(This->display, This->wnd, This->width, This->height, This->xwin.depth);
		XCopyArea(This->display, This->wnd, contents, This->xwin.gc, 0, 0, This->width, This->height, 0, 0);
	}

	ui_destroy_window(This);
	This->fullscreen = !This->fullscreen;
	ui_create_window(This);

	XDefineCursor(This->display, This->wnd, This->xwin.current_cursor);

	if (!This->ownbackstore)
	{
		XCopyArea(This->display, contents, This->wnd, This->xwin.gc, 0, 0, This->width, This->height, 0, 0);
		XFreePixmap(This->display, contents);
	}
}