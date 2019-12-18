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
typedef  int /*<<< orphan*/  pdf_annot ;
struct TYPE_3__ {float x0; float y0; float x1; float y1; } ;
typedef  TYPE_1__ fz_rect ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,float,float,float,float) ; 
 int /*<<< orphan*/  maybe_stroke_and_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 float pdf_write_border_appearance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_write_interior_fill_color_appearance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_write_stroke_color_appearance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pdf_write_square_appearance(fz_context *ctx, pdf_annot *annot, fz_buffer *buf, fz_rect *rect)
{
	float x, y, w, h;
	float lw;
	int sc;
	int ic;

	lw = pdf_write_border_appearance(ctx, annot, buf);
	sc = pdf_write_stroke_color_appearance(ctx, annot, buf);
	ic = pdf_write_interior_fill_color_appearance(ctx, annot, buf);

	x = rect->x0 + lw;
	y = rect->y0 + lw;
	w = rect->x1 - x - lw;
	h = rect->y1 - y - lw;

	fz_append_printf(ctx, buf, "%g %g %g %g re\n", x, y, w, h);
	maybe_stroke_and_fill(ctx, buf, sc, ic);
}