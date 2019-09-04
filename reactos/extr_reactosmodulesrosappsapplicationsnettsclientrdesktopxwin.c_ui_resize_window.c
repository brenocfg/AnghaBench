#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; } ;
typedef  TYPE_2__ XSizeHints ;
struct TYPE_8__ {int /*<<< orphan*/  backstore; int /*<<< orphan*/  gc; int /*<<< orphan*/  screen; int /*<<< orphan*/  depth; } ;
struct TYPE_10__ {TYPE_1__ xwin; int /*<<< orphan*/  display; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  wnd; scalar_t__ embed_wnd; scalar_t__ fullscreen; } ;
typedef  TYPE_3__ RDPCLIENT ;
typedef  int /*<<< orphan*/  Pixmap ;

/* Variables and functions */
 int /*<<< orphan*/  BlackPixelOfScreen (int /*<<< orphan*/ ) ; 
 int PMaxSize ; 
 int PMinSize ; 
 TYPE_2__* XAllocSizeHints () ; 
 int /*<<< orphan*/  XCopyArea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCreatePixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFillRectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFree (TYPE_2__*) ; 
 int /*<<< orphan*/  XFreePixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XResizeWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetForeground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetWMNormalHints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

void
ui_resize_window(RDPCLIENT * This)
{
	XSizeHints *sizehints;
	Pixmap bs;

	sizehints = XAllocSizeHints();
	if (sizehints)
	{
		sizehints->flags = PMinSize | PMaxSize;
		sizehints->min_width = sizehints->max_width = This->width;
		sizehints->min_height = sizehints->max_height = This->height;
		XSetWMNormalHints(This->display, This->wnd, sizehints);
		XFree(sizehints);
	}

	if (!(This->fullscreen || This->embed_wnd))
	{
		XResizeWindow(This->display, This->wnd, This->width, This->height);
	}

	/* create new backstore pixmap */
	if (This->xwin.backstore != 0)
	{
		bs = XCreatePixmap(This->display, This->wnd, This->width, This->height, This->xwin.depth);
		XSetForeground(This->display, This->xwin.gc, BlackPixelOfScreen(This->xwin.screen));
		XFillRectangle(This->display, bs, This->xwin.gc, 0, 0, This->width, This->height);
		XCopyArea(This->display, This->xwin.backstore, bs, This->xwin.gc, 0, 0, This->width, This->height, 0, 0);
		XFreePixmap(This->display, This->xwin.backstore);
		This->xwin.backstore = bs;
	}
}