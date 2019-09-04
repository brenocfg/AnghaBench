#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vncBuffer ;
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_3__ {int style; int /*<<< orphan*/  pattern; } ;
typedef  int /*<<< orphan*/  HGLYPH ;
typedef  TYPE_1__ BRUSH ;

/* Variables and functions */
#define  ROP2_COPY 129 
#define  ROP2_XOR 128 
 int /*<<< orphan*/  server ; 
 scalar_t__ ui_create_glyph (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_destroy_glyph (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unimpl (char*,int,...) ; 
 int /*<<< orphan*/  vncCopyBlitFrom (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vncGetPixel (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * vncNewBuffer (int,int,int) ; 
 int /*<<< orphan*/  vncSetPixel (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  vncSetRect (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  vncXorBlitFrom (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vncwinClipRect (int*,int*,int*,int*) ; 

void
ui_patblt(uint8 opcode,
	  /* dest */ int x, int y, int cx, int cy,
	  /* brush */ BRUSH * brush, int bgcolour, int fgcolour)
{
	switch (brush->style)
	{
		case 0:	/* Solid */
			switch (opcode)
			{
				case ROP2_XOR:
					{
						int xx, yy;
						vncBuffer *fill = vncNewBuffer(cx, cy, 8);
						for (yy = 0; yy < cy; yy++)
							for (xx = 0; xx < cx; xx++)
								vncSetPixel(fill, xx, yy, fgcolour);
						if (vncwinClipRect(&x, &y, &cx, &cy))
							vncXorBlitFrom(server, x, y, cx, cy, fill,
								       0, 0);
						break;
					}

				default:
					if (vncwinClipRect(&x, &y, &cx, &cy))
						vncSetRect(server, x, y, cx, cy, fgcolour);
			}
			break;

		case 3:	/* Pattern */
			{
				int xx, yy;
				vncBuffer *fill;
				fill = (vncBuffer *) ui_create_glyph(8, 8, brush->pattern);

				for (yy = 0; yy < 8; yy++)
				{
					for (xx = 0; xx < 8; xx++)
					{
						vncSetPixel(fill, xx, yy,
							    vncGetPixel(fill, xx,
									yy) ? fgcolour : bgcolour);
					}
				}

				if (vncwinClipRect(&x, &y, &cx, &cy))
				{
					switch (opcode)
					{
						case ROP2_COPY:
							vncCopyBlitFrom(server, x, y, cx, cy, fill,
									0, 0);
							break;
						case ROP2_XOR:
							vncXorBlitFrom(server, x, y, cx, cy, fill,
								       0, 0);
							break;
						default:
							unimpl("pattern blit (%d,%d) opcode=%d bg=%d fg=%d\n", x, y, opcode, bgcolour, fgcolour);
							vncCopyBlitFrom(server, x, y, cx, cy, fill,
									0, 0);
							break;
					}
				}

				ui_destroy_glyph((HGLYPH) fill);
				break;

			}
		default:
			unimpl("brush %d\n", brush->style);
	}
}