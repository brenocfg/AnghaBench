#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  XImage ;
struct TYPE_8__ {scalar_t__ yoffset; scalar_t__ xoffset; int /*<<< orphan*/  wnd; } ;
struct TYPE_6__ {int bpp; int /*<<< orphan*/  gc; int /*<<< orphan*/  backstore; int /*<<< orphan*/  depth; int /*<<< orphan*/  visual; } ;
struct TYPE_7__ {TYPE_1__ xwin; int /*<<< orphan*/  wnd; int /*<<< orphan*/  display; scalar_t__ ownbackstore; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  BitmapPad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ON_ALL_SEAMLESS_WINDOWS (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCopyArea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/ * XCreateImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XPutImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  ZPixmap ; 
 int /*<<< orphan*/ * cache_get_desktop (TYPE_2__*,int,int,int,int) ; 
 TYPE_4__* sw ; 

void
ui_desktop_restore(RDPCLIENT * This, uint32 offset, int x, int y, int cx, int cy)
{
	XImage *image;
	uint8 *data;

	offset *= This->xwin.bpp / 8;
	data = cache_get_desktop(This, offset, cx, cy, This->xwin.bpp / 8);
	if (data == NULL)
		return;

	image = XCreateImage(This->display, This->xwin.visual, This->xwin.depth, ZPixmap, 0,
			     (char *) data, cx, cy, BitmapPad(This->display), cx * This->xwin.bpp / 8);

	if (This->ownbackstore)
	{
		XPutImage(This->display, This->xwin.backstore, This->xwin.gc, image, 0, 0, x, y, cx, cy);
		XCopyArea(This->display, This->xwin.backstore, This->wnd, This->xwin.gc, x, y, cx, cy, x, y);
		ON_ALL_SEAMLESS_WINDOWS(XCopyArea,
					(This->display, This->xwin.backstore, sw->wnd, This->xwin.gc,
					 x, y, cx, cy, x - sw->xoffset, y - sw->yoffset));
	}
	else
	{
		XPutImage(This->display, This->wnd, This->xwin.gc, image, 0, 0, x, y, cx, cy);
		ON_ALL_SEAMLESS_WINDOWS(XCopyArea,
					(This->display, This->wnd, sw->wnd, This->xwin.gc, x, y, cx, cy,
					 x - sw->xoffset, y - sw->yoffset));
	}

	XFree(image);
}