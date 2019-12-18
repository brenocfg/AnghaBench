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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  XPoint ;
struct TYPE_10__ {int style; int* pattern; int /*<<< orphan*/  yorigin; int /*<<< orphan*/  xorigin; } ;
struct TYPE_8__ {int /*<<< orphan*/  gc; } ;
struct TYPE_9__ {TYPE_1__ xwin; int /*<<< orphan*/  display; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  Pixmap ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  HGLYPH ;
typedef  TYPE_3__ BRUSH ;

/* Variables and functions */
#define  ALTERNATE 129 
 int /*<<< orphan*/  EvenOddRule ; 
 int /*<<< orphan*/  FILL_POLYGON (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FillOpaqueStippled ; 
 int /*<<< orphan*/  FillSolid ; 
 int /*<<< orphan*/  RESET_FUNCTION (int) ; 
 int /*<<< orphan*/  SET_BACKGROUND (int) ; 
 int /*<<< orphan*/  SET_FOREGROUND (int) ; 
 int /*<<< orphan*/  SET_FUNCTION (int) ; 
#define  WINDING 128 
 int /*<<< orphan*/  WindingRule ; 
 int /*<<< orphan*/  XSetFillRule (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetFillStyle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetStipple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetTSOrigin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hatch_patterns ; 
 int /*<<< orphan*/  ui_create_glyph (TYPE_2__*,int,int,int*) ; 
 int /*<<< orphan*/  ui_destroy_glyph (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

void
ui_polygon(RDPCLIENT * This, uint8 opcode,
	   /* mode */ uint8 fillmode,
	   /* dest */ POINT * point, int npoints,
	   /* brush */ BRUSH * brush, int bgcolour, int fgcolour)
{
	uint8 style, i, ipattern[8];
	Pixmap fill;

	SET_FUNCTION(opcode);

	switch (fillmode)
	{
		case ALTERNATE:
			XSetFillRule(This->display, This->xwin.gc, EvenOddRule);
			break;
		case WINDING:
			XSetFillRule(This->display, This->xwin.gc, WindingRule);
			break;
		default:
			unimpl("fill mode %d\n", fillmode);
	}

	if (brush)
		style = brush->style;
	else
		style = 0;

	switch (style)
	{
		case 0:	/* Solid */
			SET_FOREGROUND(fgcolour);
			FILL_POLYGON((XPoint *) point, npoints);
			break;

		case 2:	/* Hatch */
			fill = (Pixmap) ui_create_glyph(This, 8, 8,
							hatch_patterns + brush->pattern[0] * 8);
			SET_FOREGROUND(fgcolour);
			SET_BACKGROUND(bgcolour);
			XSetFillStyle(This->display, This->xwin.gc, FillOpaqueStippled);
			XSetStipple(This->display, This->xwin.gc, fill);
			XSetTSOrigin(This->display, This->xwin.gc, brush->xorigin, brush->yorigin);
			FILL_POLYGON((XPoint *) point, npoints);
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
			FILL_POLYGON((XPoint *) point, npoints);
			XSetFillStyle(This->display, This->xwin.gc, FillSolid);
			XSetTSOrigin(This->display, This->xwin.gc, 0, 0);
			ui_destroy_glyph(This, (HGLYPH) fill);
			break;

		default:
			unimpl("brush %d\n", brush->style);
	}

	RESET_FUNCTION(opcode);
}