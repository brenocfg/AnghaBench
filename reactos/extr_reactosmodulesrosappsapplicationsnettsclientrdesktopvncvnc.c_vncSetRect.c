#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vncPixel ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  TYPE_2__* rfbScreenInfoPtr ;
struct TYPE_5__ {int bitsPerPixel; } ;
struct TYPE_6__ {int width; int height; int paddedWidthInBytes; int /*<<< orphan*/ * frameBuffer; TYPE_1__ serverFormat; } ;

/* Variables and functions */
 int /*<<< orphan*/  SETPIXEL (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frameBuffer ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rfbMarkRectAsModified (TYPE_2__*,int,int,int,int) ; 
 int /*<<< orphan*/  vncHideCursor () ; 

void
vncSetRect(rfbScreenInfoPtr s, int x, int y, int w, int h, vncPixel c)
{
	int xx, yy;

	if (x + w > s->width)
		w = s->width - x;
	if (y + h > s->height)
		h = s->height - y;
	if (w <= 0 || h <= 0)
		return;

	vncHideCursor();

	// - Fill the rect in the local framebuffer
	if (s->serverFormat.bitsPerPixel == 8)
	{
		// - Simple 8-bit fill
		uint8_t *dstdata;
		dstdata = s->frameBuffer + (y * s->paddedWidthInBytes + x);
		for (yy = 0; yy < h; yy++)
		{
			memset(dstdata, c, w);
			dstdata += s->paddedWidthInBytes;
		}
	}
	else
	{
		for (yy = y; yy < y + h; yy++)
		{
			for (xx = x; xx < x + w; xx++)
			{
				SETPIXEL(frameBuffer, xx, yy, c);
			}
		}
	}

	rfbMarkRectAsModified(s, x, y, x + w, y + h);
}