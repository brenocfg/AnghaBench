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
struct TYPE_10__ {int style; int* pattern; int /*<<< orphan*/  yorigin; int /*<<< orphan*/  xorigin; } ;
struct TYPE_8__ {int /*<<< orphan*/  gc; } ;
struct TYPE_9__ {TYPE_1__ xwin; int /*<<< orphan*/  display; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  Pixmap ;
typedef  int /*<<< orphan*/  HGLYPH ;
typedef  TYPE_3__ BRUSH ;

/* Variables and functions */
 int /*<<< orphan*/  DRAW_ELLIPSE (int,int,int,int,int) ; 
 int /*<<< orphan*/  FillOpaqueStippled ; 
 int /*<<< orphan*/  FillSolid ; 
 int /*<<< orphan*/  RESET_FUNCTION (int) ; 
 int /*<<< orphan*/  SET_BACKGROUND (int) ; 
 int /*<<< orphan*/  SET_FOREGROUND (int) ; 
 int /*<<< orphan*/  SET_FUNCTION (int) ; 
 int /*<<< orphan*/  XSetFillStyle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetStipple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetTSOrigin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hatch_patterns ; 
 int /*<<< orphan*/  ui_create_glyph (TYPE_2__*,int,int,int*) ; 
 int /*<<< orphan*/  ui_destroy_glyph (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

void
ui_ellipse(RDPCLIENT * This, uint8 opcode,
	   /* mode */ uint8 fillmode,
	   /* dest */ int x, int y, int cx, int cy,
	   /* brush */ BRUSH * brush, int bgcolour, int fgcolour)
{
	uint8 style, i, ipattern[8];
	Pixmap fill;

	SET_FUNCTION(opcode);

	if (brush)
		style = brush->style;
	else
		style = 0;

	switch (style)
	{
		case 0:	/* Solid */
			SET_FOREGROUND(fgcolour);
			DRAW_ELLIPSE(x, y, cx, cy, fillmode);
			break;

		case 2:	/* Hatch */
			fill = (Pixmap) ui_create_glyph(This, 8, 8,
							hatch_patterns + brush->pattern[0] * 8);
			SET_FOREGROUND(fgcolour);
			SET_BACKGROUND(bgcolour);
			XSetFillStyle(This->display, This->xwin.gc, FillOpaqueStippled);
			XSetStipple(This->display, This->xwin.gc, fill);
			XSetTSOrigin(This->display, This->xwin.gc, brush->xorigin, brush->yorigin);
			DRAW_ELLIPSE(x, y, cx, cy, fillmode);
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
			DRAW_ELLIPSE(x, y, cx, cy, fillmode);
			XSetFillStyle(This->display, This->xwin.gc, FillSolid);
			XSetTSOrigin(This->display, This->xwin.gc, 0, 0);
			ui_destroy_glyph(This, (HGLYPH) fill);
			break;

		default:
			unimpl("brush %d\n", brush->style);
	}

	RESET_FUNCTION(opcode);
}