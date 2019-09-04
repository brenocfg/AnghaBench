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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint32 ;
struct TYPE_9__ {scalar_t__ data; int /*<<< orphan*/  bytes_per_line; } ;
typedef  TYPE_2__ XImage ;
struct TYPE_8__ {int bpp; int /*<<< orphan*/  gc; int /*<<< orphan*/  depth; int /*<<< orphan*/  backstore; } ;
struct TYPE_10__ {TYPE_1__ xwin; int /*<<< orphan*/  display; int /*<<< orphan*/  wnd; scalar_t__ ownbackstore; } ;
typedef  TYPE_3__ RDPCLIENT ;
typedef  int /*<<< orphan*/  Pixmap ;

/* Variables and functions */
 int /*<<< orphan*/  AllPlanes ; 
 int /*<<< orphan*/  XCopyArea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCreatePixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDestroyImage (TYPE_2__*) ; 
 int /*<<< orphan*/  XFreePixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* XGetImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPixmap ; 
 int /*<<< orphan*/  cache_put_desktop (TYPE_3__*,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void
ui_desktop_save(RDPCLIENT * This, uint32 offset, int x, int y, int cx, int cy)
{
	Pixmap pix;
	XImage *image;

	if (This->ownbackstore)
	{
		image = XGetImage(This->display, This->xwin.backstore, x, y, cx, cy, AllPlanes, ZPixmap);
	}
	else
	{
		pix = XCreatePixmap(This->display, This->wnd, cx, cy, This->xwin.depth);
		XCopyArea(This->display, This->wnd, pix, This->xwin.gc, x, y, cx, cy, 0, 0);
		image = XGetImage(This->display, pix, 0, 0, cx, cy, AllPlanes, ZPixmap);
		XFreePixmap(This->display, pix);
	}

	offset *= This->xwin.bpp / 8;
	cache_put_desktop(This, offset, cx, cy, image->bytes_per_line, This->xwin.bpp / 8, (uint8 *) image->data);

	XDestroyImage(image);
}