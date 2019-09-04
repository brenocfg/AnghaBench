#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
struct TYPE_12__ {scalar_t__ yoffset; scalar_t__ xoffset; int /*<<< orphan*/  wnd; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {int /*<<< orphan*/  gc; int /*<<< orphan*/  backstore; } ;
struct TYPE_10__ {int width; TYPE_1__ xwin; int /*<<< orphan*/  display; int /*<<< orphan*/  wnd; scalar_t__ ownbackstore; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  FONTGLYPH ;
typedef  TYPE_3__ DATABLOB ;
typedef  int /*<<< orphan*/  BRUSH ;

/* Variables and functions */
 int /*<<< orphan*/  DO_GLYPH (int*,int) ; 
 int /*<<< orphan*/  FILL_RECTANGLE_BACKSTORE (int,int,int,int) ; 
 int /*<<< orphan*/  FillSolid ; 
 int /*<<< orphan*/  FillStippled ; 
 int MIX_OPAQUE ; 
 int /*<<< orphan*/  ON_ALL_SEAMLESS_WINDOWS (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_BACKGROUND (int) ; 
 int /*<<< orphan*/  SET_FOREGROUND (int) ; 
 int TEXT2_IMPLICIT_X ; 
 int TEXT2_VERTICAL ; 
 int /*<<< orphan*/  XCopyArea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  XSetFillStyle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* cache_get_text (TYPE_2__*,int) ; 
 int /*<<< orphan*/  cache_put_text (TYPE_2__*,int,int*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_5__* sw ; 
 int /*<<< orphan*/  warning (char*) ; 

void
ui_draw_text(RDPCLIENT * This, uint8 font, uint8 flags, uint8 opcode, int mixmode, int x, int y,
	     int clipx, int clipy, int clipcx, int clipcy,
	     int boxx, int boxy, int boxcx, int boxcy, BRUSH * brush,
	     int bgcolour, int fgcolour, uint8 * text, uint8 length)
{
	/* TODO: use brush appropriately */

	FONTGLYPH *glyph;
	int i, j, xyoffset, x1, y1;
	DATABLOB *entry;

	SET_FOREGROUND(bgcolour);

	/* Sometimes, the boxcx value is something really large, like
	   32691. This makes XCopyArea fail with Xvnc. The code below
	   is a quick fix. */
	if (boxx + boxcx > This->width)
		boxcx = This->width - boxx;

	if (boxcx > 1)
	{
		FILL_RECTANGLE_BACKSTORE(boxx, boxy, boxcx, boxcy);
	}
	else if (mixmode == MIX_OPAQUE)
	{
		FILL_RECTANGLE_BACKSTORE(clipx, clipy, clipcx, clipcy);
	}

	SET_FOREGROUND(fgcolour);
	SET_BACKGROUND(bgcolour);
	XSetFillStyle(This->display, This->xwin.gc, FillStippled);

	/* Paint text, character by character */
	for (i = 0; i < length;)
	{
		switch (text[i])
		{
			case 0xff:
				/* At least two bytes needs to follow */
				if (i + 3 > length)
				{
					warning("Skipping short 0xff command:");
					for (j = 0; j < length; j++)
						fprintf(stderr, "%02x ", text[j]);
					fprintf(stderr, "\n");
					i = length = 0;
					break;
				}
				cache_put_text(This, text[i + 1], text, text[i + 2]);
				i += 3;
				length -= i;
				/* this will move pointer from start to first character after FF command */
				text = &(text[i]);
				i = 0;
				break;

			case 0xfe:
				/* At least one byte needs to follow */
				if (i + 2 > length)
				{
					warning("Skipping short 0xfe command:");
					for (j = 0; j < length; j++)
						fprintf(stderr, "%02x ", text[j]);
					fprintf(stderr, "\n");
					i = length = 0;
					break;
				}
				entry = cache_get_text(This, text[i + 1]);
				if (entry->data != NULL)
				{
					if ((((uint8 *) (entry->data))[1] == 0)
					    && (!(flags & TEXT2_IMPLICIT_X)) && (i + 2 < length))
					{
						if (flags & TEXT2_VERTICAL)
							y += text[i + 2];
						else
							x += text[i + 2];
					}
					for (j = 0; j < entry->size; j++)
						DO_GLYPH(((uint8 *) (entry->data)), j);
				}
				if (i + 2 < length)
					i += 3;
				else
					i += 2;
				length -= i;
				/* this will move pointer from start to first character after FE command */
				text = &(text[i]);
				i = 0;
				break;

			default:
				DO_GLYPH(text, i);
				i++;
				break;
		}
	}

	XSetFillStyle(This->display, This->xwin.gc, FillSolid);

	if (This->ownbackstore)
	{
		if (boxcx > 1)
		{
			XCopyArea(This->display, This->xwin.backstore, This->wnd, This->xwin.gc, boxx,
				  boxy, boxcx, boxcy, boxx, boxy);
			ON_ALL_SEAMLESS_WINDOWS(XCopyArea,
						(This->display, This->xwin.backstore, sw->wnd, This->xwin.gc,
						 boxx, boxy,
						 boxcx, boxcy,
						 boxx - sw->xoffset, boxy - sw->yoffset));
		}
		else
		{
			XCopyArea(This->display, This->xwin.backstore, This->wnd, This->xwin.gc, clipx,
				  clipy, clipcx, clipcy, clipx, clipy);
			ON_ALL_SEAMLESS_WINDOWS(XCopyArea,
						(This->display, This->xwin.backstore, sw->wnd, This->xwin.gc,
						 clipx, clipy,
						 clipcx, clipcy, clipx - sw->xoffset,
						 clipy - sw->yoffset));
		}
	}
}