#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vncBuffer ;
typedef  int /*<<< orphan*/  HGLYPH ;

/* Variables and functions */
#define  MIX_OPAQUE 129 
#define  MIX_TRANSPARENT 128 
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 
 int /*<<< orphan*/  vncCopyBlitFrom (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vncDeleteBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vncDupBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ vncGetPixel (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vncSetPixel (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  vncTransBlitFrom (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  vncwinClipRect (int*,int*,int*,int*) ; 

void
ui_draw_glyph(int mixmode,
	      /* dest */ int x, int y, int cx, int cy,
	      /* src */ HGLYPH glyph, int srcx, int srcy,
	      /* colours */ int bgcolour, int fgcolour)
{
	int xx, yy;
	int ox, oy;
	vncBuffer *buf = vncDupBuffer(glyph);

	x &= 0xffff;
	y &= 0xffff;

	/* yes, sometimes same fgcolour and bgcolour are sent, but because
	 * of transparency, we have to change that! */
	if (mixmode == MIX_TRANSPARENT && fgcolour == bgcolour)
		bgcolour = fgcolour ^ 0xff;

	ox = x;
	oy = y;

	for (yy = srcy; yy < srcy + cy; yy++)
	{
		for (xx = srcx; xx < srcx + cx; xx++)
		{
			vncSetPixel(buf, xx, yy, vncGetPixel(buf, xx, yy) ? fgcolour : bgcolour);
		}
	}

	switch (mixmode)
	{
		case MIX_TRANSPARENT:
			if (vncwinClipRect(&x, &y, &cx, &cy))
			{
				//if we clipped top or left, we have to adjust srcx,srcy;
				srcx += x - ox;
				srcy += y - oy;
				vncTransBlitFrom(server, x, y, cx, cy, buf, srcx, srcy, bgcolour);
			}
			break;
		case MIX_OPAQUE:
			if (vncwinClipRect(&x, &y, &cx, &cy))
			{
				//if we clipped top or left, we have to adjust srcx,srcy;
				srcx += x - ox;
				srcy += y - oy;
				vncCopyBlitFrom(server, x, y, cx, cy, buf, srcx, srcy);
			}
			break;

		default:
			unimpl("mix %d\n", mixmode);
	}
	vncDeleteBuffer(buf);
}