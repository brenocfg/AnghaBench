#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vncPixel ;
struct TYPE_10__ {int w; int h; int linew; int /*<<< orphan*/ * data; TYPE_2__* format; } ;
typedef  TYPE_3__ vncBuffer ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  TYPE_4__* rfbScreenInfoPtr ;
struct TYPE_8__ {scalar_t__ bitsPerPixel; } ;
struct TYPE_11__ {int paddedWidthInBytes; int /*<<< orphan*/ * frameBuffer; TYPE_1__ serverFormat; } ;
struct TYPE_9__ {scalar_t__ bitsPerPixel; } ;

/* Variables and functions */
 int /*<<< orphan*/  GETPIXEL (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  SETPIXEL (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frameBuffer ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vncHideCursor () ; 

void
vncCopyBlitFromNoEncode(rfbScreenInfoPtr s, int x, int y, int w, int h,
			vncBuffer * src, int srcx, int srcy)
{
	int xx, yy;

	vncHideCursor();

	if (s->serverFormat.bitsPerPixel == src->format->bitsPerPixel
	    && srcx + w <= src->w && srcy + h <= src->h)
	{
		//simple copy
		uint8_t *srcdata, *dstdata;
		srcdata = src->data + (srcy * src->linew + srcx);
		dstdata = s->frameBuffer + (y * s->paddedWidthInBytes + x);
		for (yy = 0; yy < h; yy++)
		{
			memcpy(dstdata, srcdata, w);
			dstdata += s->paddedWidthInBytes;
			srcdata += src->linew;
		}
	}
	else
	{
		// xsrc,ysrc provide tiling copy support.
		for (yy = y; yy < y + h; yy++)
		{
			int ysrc = srcy + yy - y;
			while (ysrc >= src->h)
				ysrc -= src->h;
			for (xx = x; xx < x + w; xx++)
			{
				vncPixel p;
				int xsrc = srcx + xx - x;
				while (xsrc >= src->linew)
					xsrc -= src->linew;
				p = GETPIXEL(src, xsrc, ysrc);
				SETPIXEL(frameBuffer, xx, yy, p);
			}
		}
	}
}