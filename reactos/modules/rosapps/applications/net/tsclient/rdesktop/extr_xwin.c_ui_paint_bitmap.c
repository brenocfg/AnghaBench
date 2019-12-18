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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  XImage ;
struct TYPE_8__ {scalar_t__ yoffset; scalar_t__ xoffset; int /*<<< orphan*/  wnd; } ;
struct TYPE_6__ {int bpp; int /*<<< orphan*/  gc; int /*<<< orphan*/  backstore; int /*<<< orphan*/  depth; int /*<<< orphan*/  visual; } ;
struct TYPE_7__ {int server_depth; TYPE_1__ xwin; int /*<<< orphan*/  wnd; int /*<<< orphan*/  display; scalar_t__ ownbackstore; scalar_t__ owncolmap; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  ON_ALL_SEAMLESS_WINDOWS (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCopyArea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/ * XCreateImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XPutImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  ZPixmap ; 
 TYPE_5__* sw ; 
 int /*<<< orphan*/ * translate_image (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

void
ui_paint_bitmap(RDPCLIENT * This, int x, int y, int cx, int cy, int width, int height, uint8 * data)
{
	XImage *image;
	uint8 *tdata;
	int bitmap_pad;

	if (This->server_depth == 8)
	{
		bitmap_pad = 8;
	}
	else
	{
		bitmap_pad = This->xwin.bpp;

		if (This->xwin.bpp == 24)
			bitmap_pad = 32;
	}

	tdata = (This->owncolmap ? data : translate_image(This, width, height, data));
	image = XCreateImage(This->display, This->xwin.visual, This->xwin.depth, ZPixmap, 0,
			     (char *) tdata, width, height, bitmap_pad, 0);

	if (This->ownbackstore)
	{
		XPutImage(This->display, This->xwin.backstore, This->xwin.gc, image, 0, 0, x, y, cx, cy);
		XCopyArea(This->display, This->xwin.backstore, This->wnd, This->xwin.gc, x, y, cx, cy, x, y);
		ON_ALL_SEAMLESS_WINDOWS(XCopyArea,
					(This->display, This->xwin.backstore, sw->wnd, This->xwin.gc, x, y, cx, cy,
					 x - sw->xoffset, y - sw->yoffset));
	}
	else
	{
		XPutImage(This->display, This->wnd, This->xwin.gc, image, 0, 0, x, y, cx, cy);
		ON_ALL_SEAMLESS_WINDOWS(XCopyArea,
					(This->display, This->wnd, sw->wnd, This->xwin.gc, x, y, cx, cy,
					 x - sw->xoffset, y - sw->yoffset));
	}

	XFree(image);
	if (tdata != data)
		xfree(tdata);
}