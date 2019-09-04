#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
struct TYPE_12__ {scalar_t__ yoffset; scalar_t__ xoffset; int /*<<< orphan*/  wnd; } ;
struct TYPE_11__ {int style; int* pattern; int /*<<< orphan*/  yorigin; int /*<<< orphan*/  xorigin; } ;
struct TYPE_9__ {int /*<<< orphan*/  gc; int /*<<< orphan*/  backstore; } ;
struct TYPE_10__ {TYPE_1__ xwin; int /*<<< orphan*/  wnd; scalar_t__ ownbackstore; int /*<<< orphan*/  display; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  Pixmap ;
typedef  int /*<<< orphan*/  HGLYPH ;
typedef  TYPE_3__ BRUSH ;

/* Variables and functions */
 int /*<<< orphan*/  FILL_RECTANGLE_BACKSTORE (int,int,int,int) ; 
 int /*<<< orphan*/  FillOpaqueStippled ; 
 int /*<<< orphan*/  FillSolid ; 
 int /*<<< orphan*/  ON_ALL_SEAMLESS_WINDOWS (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESET_FUNCTION (int) ; 
 int /*<<< orphan*/  SET_BACKGROUND (int) ; 
 int /*<<< orphan*/  SET_FOREGROUND (int) ; 
 int /*<<< orphan*/  SET_FUNCTION (int) ; 
 int /*<<< orphan*/  XCopyArea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  XSetFillStyle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetStipple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetTSOrigin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hatch_patterns ; 
 TYPE_8__* sw ; 
 int /*<<< orphan*/  ui_create_glyph (TYPE_2__*,int,int,int*) ; 
 int /*<<< orphan*/  ui_destroy_glyph (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

void
ui_patblt(RDPCLIENT * This, uint8 opcode,
	  /* dest */ int x, int y, int cx, int cy,
	  /* brush */ BRUSH * brush, int bgcolour, int fgcolour)
{
	Pixmap fill;
	uint8 i, ipattern[8];

	SET_FUNCTION(opcode);

	switch (brush->style)
	{
		case 0:	/* Solid */
			SET_FOREGROUND(fgcolour);
			FILL_RECTANGLE_BACKSTORE(x, y, cx, cy);
			break;

		case 2:	/* Hatch */
			fill = (Pixmap) ui_create_glyph(This, 8, 8,
							hatch_patterns + brush->pattern[0] * 8);
			SET_FOREGROUND(fgcolour);
			SET_BACKGROUND(bgcolour);
			XSetFillStyle(This->display, This->xwin.gc, FillOpaqueStippled);
			XSetStipple(This->display, This->xwin.gc, fill);
			XSetTSOrigin(This->display, This->xwin.gc, brush->xorigin, brush->yorigin);
			FILL_RECTANGLE_BACKSTORE(x, y, cx, cy);
			XSetFillStyle(This->display, This->xwin.gc, FillSolid);
			XSetTSOrigin(This->display, This->xwin.gc, 0, 0);
			ui_destroy_glyph(This, (HGLYPH) fill);
			break;

		case 3:	/* Pattern */
			for (i = 0; i != 8; i++)
				ipattern[7 - i] = brush->pattern[i];
			fill = (Pixmap) ui_create_glyph(This, 8, 8, ipattern);
			SET_FOREGROUND(bgcolour);
			SET_BACKGROUND(fgcolour);
			XSetFillStyle(This->display, This->xwin.gc, FillOpaqueStippled);
			XSetStipple(This->display, This->xwin.gc, fill);
			XSetTSOrigin(This->display, This->xwin.gc, brush->xorigin, brush->yorigin);
			FILL_RECTANGLE_BACKSTORE(x, y, cx, cy);
			XSetFillStyle(This->display, This->xwin.gc, FillSolid);
			XSetTSOrigin(This->display, This->xwin.gc, 0, 0);
			ui_destroy_glyph(This, (HGLYPH) fill);
			break;

		default:
			unimpl("brush %d\n", brush->style);
	}

	RESET_FUNCTION(opcode);

	if (This->ownbackstore)
		XCopyArea(This->display, This->xwin.backstore, This->wnd, This->xwin.gc, x, y, cx, cy, x, y);
	ON_ALL_SEAMLESS_WINDOWS(XCopyArea,
				(This->display, This->ownbackstore ? This->xwin.backstore : This->wnd, sw->wnd, This->xwin.gc,
				 x, y, cx, cy, x - sw->xoffset, y - sw->yoffset));
}