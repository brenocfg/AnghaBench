#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  gc; } ;
struct TYPE_5__ {TYPE_1__ xwin; int /*<<< orphan*/  display; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  Pixmap ;
typedef  scalar_t__ HGLYPH ;

/* Variables and functions */
 int /*<<< orphan*/  FILL_RECTANGLE_BACKSTORE (int,int,int,int) ; 
 int /*<<< orphan*/  FillOpaqueStippled ; 
 int /*<<< orphan*/  FillSolid ; 
 int /*<<< orphan*/  FillStippled ; 
 int MIX_TRANSPARENT ; 
 int /*<<< orphan*/  SET_BACKGROUND (int) ; 
 int /*<<< orphan*/  SET_FOREGROUND (int) ; 
 int /*<<< orphan*/  XSetFillStyle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetStipple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetTSOrigin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void
ui_draw_glyph(RDPCLIENT * This, int mixmode,
	      /* dest */ int x, int y, int cx, int cy,
	      /* src */ HGLYPH glyph, int srcx, int srcy,
	      int bgcolour, int fgcolour)
{
	SET_FOREGROUND(fgcolour);
	SET_BACKGROUND(bgcolour);

	XSetFillStyle(This->display, This->xwin.gc,
		      (mixmode == MIX_TRANSPARENT) ? FillStippled : FillOpaqueStippled);
	XSetStipple(This->display, This->xwin.gc, (Pixmap) glyph);
	XSetTSOrigin(This->display, This->xwin.gc, x, y);

	FILL_RECTANGLE_BACKSTORE(x, y, cx, cy);

	XSetFillStyle(This->display, This->xwin.gc, FillSolid);
}