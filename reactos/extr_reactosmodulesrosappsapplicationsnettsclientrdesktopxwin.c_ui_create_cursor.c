#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
struct TYPE_8__ {int red; int blue; int green; int flags; } ;
typedef  TYPE_1__ XColor ;
struct TYPE_9__ {int /*<<< orphan*/  display; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  Pixmap ;
typedef  scalar_t__ HGLYPH ;
typedef  int /*<<< orphan*/  HCURSOR ;
typedef  int /*<<< orphan*/  Cursor ;

/* Variables and functions */
 int DoBlue ; 
 int DoGreen ; 
 int DoRed ; 
 int /*<<< orphan*/  XCreatePixmapCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ui_create_glyph (TYPE_2__*,int,int,int*) ; 
 int /*<<< orphan*/  ui_destroy_glyph (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  xfree (int*) ; 
 scalar_t__ xmalloc (int) ; 

HCURSOR
ui_create_cursor(RDPCLIENT * This, unsigned int x, unsigned int y, int width, int height,
		 uint8 * andmask, uint8 * xormask)
{
	HGLYPH maskglyph, cursorglyph;
	XColor bg, fg;
	Cursor xcursor;
	uint8 *cursor, *pcursor;
	uint8 *mask, *pmask;
	uint8 nextbit;
	int scanline, offset;
	int i, j;

	scanline = (width + 7) / 8;
	offset = scanline * height;

	cursor = (uint8 *) xmalloc(offset);
	memset(cursor, 0, offset);

	mask = (uint8 *) xmalloc(offset);
	memset(mask, 0, offset);

	/* approximate AND and XOR masks with a monochrome X pointer */
	for (i = 0; i < height; i++)
	{
		offset -= scanline;
		pcursor = &cursor[offset];
		pmask = &mask[offset];

		for (j = 0; j < scanline; j++)
		{
			for (nextbit = 0x80; nextbit != 0; nextbit >>= 1)
			{
				if (xormask[0] || xormask[1] || xormask[2])
				{
					*pcursor |= (~(*andmask) & nextbit);
					*pmask |= nextbit;
				}
				else
				{
					*pcursor |= ((*andmask) & nextbit);
					*pmask |= (~(*andmask) & nextbit);
				}

				xormask += 3;
			}

			andmask++;
			pcursor++;
			pmask++;
		}
	}

	fg.red = fg.blue = fg.green = 0xffff;
	bg.red = bg.blue = bg.green = 0x0000;
	fg.flags = bg.flags = DoRed | DoBlue | DoGreen;

	cursorglyph = ui_create_glyph(This, width, height, cursor);
	maskglyph = ui_create_glyph(This, width, height, mask);

	xcursor =
		XCreatePixmapCursor(This->display, (Pixmap) cursorglyph,
				    (Pixmap) maskglyph, &fg, &bg, x, y);

	ui_destroy_glyph(This, maskglyph);
	ui_destroy_glyph(This, cursorglyph);
	xfree(mask);
	xfree(cursor);
	return (HCURSOR) xcursor;
}