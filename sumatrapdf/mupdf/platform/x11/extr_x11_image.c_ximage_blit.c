#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  bytes_per_line; scalar_t__ data; } ;
typedef  TYPE_1__ XImage ;
struct TYPE_7__ {int /*<<< orphan*/  display; scalar_t__ useshm; int /*<<< orphan*/  (* convert_func ) (unsigned char*,int,unsigned char*,int /*<<< orphan*/ ,int,int) ;} ;
typedef  int /*<<< orphan*/  GC ;
typedef  int /*<<< orphan*/  Drawable ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 scalar_t__ HEIGHT ; 
 scalar_t__ WIDTH ; 
 int /*<<< orphan*/  XPutImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  XShmPutImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int fz_mini (int,scalar_t__) ; 
 TYPE_3__ info ; 
 TYPE_1__* next_pool_image () ; 
 int /*<<< orphan*/  stub1 (unsigned char*,int,unsigned char*,int /*<<< orphan*/ ,int,int) ; 

void
ximage_blit(Drawable d, GC gc,
	int dstx, int dsty,
	unsigned char *srcdata,
	int srcx, int srcy,
	int srcw, int srch,
	int srcstride)
{
	XImage *image;
	int ax, ay;
	int w, h;
	unsigned char *srcptr;

	for (ay = 0; ay < srch; ay += HEIGHT)
	{
		h = fz_mini(srch - ay, HEIGHT);
		for (ax = 0; ax < srcw; ax += WIDTH)
		{
			w = fz_mini(srcw - ax, WIDTH);

			image = next_pool_image();

			srcptr = srcdata +
			(ay + srcy) * srcstride +
			(ax + srcx) * 4;

			info.convert_func(srcptr, srcstride,
				(unsigned char *) image->data,
				image->bytes_per_line, w, h);

			if (info.useshm)
			{
				XShmPutImage(info.display, d, gc, image,
					0, 0, dstx + ax, dsty + ay,
					w, h, False);
			}
			else
			{
				XPutImage(info.display, d, gc, image,
					0, 0,
					dstx + ax,
					dsty + ay,
					w, h);
			}
		}
	}
}