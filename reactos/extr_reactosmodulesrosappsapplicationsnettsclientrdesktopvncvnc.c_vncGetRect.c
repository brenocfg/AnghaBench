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
struct TYPE_9__ {char* data; } ;
typedef  TYPE_2__ vncBuffer ;
typedef  TYPE_3__* rfbScreenInfoPtr ;
struct TYPE_8__ {int bitsPerPixel; int /*<<< orphan*/  depth; } ;
struct TYPE_10__ {int paddedWidthInBytes; char* frameBuffer; TYPE_1__ serverFormat; } ;

/* Variables and functions */
 int /*<<< orphan*/  GETPIXEL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SETPIXEL (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frameBuffer ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  vncHideCursor () ; 
 TYPE_2__* vncNewBuffer (int,int,int /*<<< orphan*/ ) ; 

vncBuffer *
vncGetRect(rfbScreenInfoPtr s, int x, int y, int w, int h)
{
	int xx, yy;
	vncBuffer *b = vncNewBuffer(w, h, s->serverFormat.depth);

	vncHideCursor();

	if (s->serverFormat.bitsPerPixel == 8)
	{
		//simple copy
		int srcstep, dststep;
		char *srcdata, *dstdata;
		srcstep = s->paddedWidthInBytes * s->serverFormat.bitsPerPixel / 8;
		dststep = w * s->serverFormat.bitsPerPixel / 8;
		dstdata = b->data;
		srcdata = s->frameBuffer + (y * srcstep + x * s->serverFormat.bitsPerPixel / 8);
		for (yy = 0; yy < h; yy++)
		{
			memcpy(dstdata, srcdata, dststep);
			dstdata += dststep;
			srcdata += srcstep;
		}
	}
	else
	{
		for (yy = y; yy < y + h; yy++)
		{
			for (xx = x; xx < x + w; xx++)
			{
				SETPIXEL(b, xx - x, yy - y, GETPIXEL(frameBuffer, xx, yy));
			}
		}
	}

	return b;
}