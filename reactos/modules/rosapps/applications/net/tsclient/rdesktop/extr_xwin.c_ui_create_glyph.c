#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_10__ {void* bitmap_bit_order; void* byte_order; } ;
typedef  TYPE_2__ XImage ;
struct TYPE_9__ {int /*<<< orphan*/  create_glyph_gc; int /*<<< orphan*/  visual; } ;
struct TYPE_11__ {TYPE_1__ xwin; int /*<<< orphan*/  display; int /*<<< orphan*/  wnd; } ;
typedef  TYPE_3__ RDPCLIENT ;
typedef  int /*<<< orphan*/  Pixmap ;
typedef  int /*<<< orphan*/  HGLYPH ;

/* Variables and functions */
 void* MSBFirst ; 
 int /*<<< orphan*/  XCreateGC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* XCreateImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  XCreatePixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  XFree (TYPE_2__*) ; 
 int /*<<< orphan*/  XInitImage (TYPE_2__*) ; 
 int /*<<< orphan*/  XPutImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ZPixmap ; 

HGLYPH
ui_create_glyph(RDPCLIENT * This, int width, int height, const uint8 * data)
{
	XImage *image;
	Pixmap bitmap;
	int scanline;

	scanline = (width + 7) / 8;

	bitmap = XCreatePixmap(This->display, This->wnd, width, height, 1);
	if (This->xwin.create_glyph_gc == 0)
		This->xwin.create_glyph_gc = XCreateGC(This->display, bitmap, 0, NULL);

	image = XCreateImage(This->display, This->xwin.visual, 1, ZPixmap, 0, (char *) data,
			     width, height, 8, scanline);
	image->byte_order = MSBFirst;
	image->bitmap_bit_order = MSBFirst;
	XInitImage(image);

	XPutImage(This->display, bitmap, This->xwin.create_glyph_gc, image, 0, 0, 0, 0, width, height);

	XFree(image);
	return (HGLYPH) bitmap;
}