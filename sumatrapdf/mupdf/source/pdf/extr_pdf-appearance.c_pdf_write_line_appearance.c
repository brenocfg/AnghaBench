#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_12__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
struct TYPE_13__ {void* y1; void* x1; void* y0; void* x0; } ;
typedef  TYPE_2__ fz_rect ;
struct TYPE_14__ {int x; int y; } ;
typedef  TYPE_3__ fz_point ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  L ; 
 int /*<<< orphan*/  LE ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int,int,int) ; 
 TYPE_2__ fz_expand_rect (TYPE_2__,void*) ; 
 void* fz_max (int,float) ; 
 void* fz_min (int,int) ; 
 int /*<<< orphan*/  maybe_stroke (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* pdf_array_get_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float pdf_write_border_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int pdf_write_interior_fill_color_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_write_line_cap_appearance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,float,float,float,float,float,int,int,int /*<<< orphan*/ ) ; 
 int pdf_write_stroke_color_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 float sqrtf (float) ; 

__attribute__((used)) static void
pdf_write_line_appearance(fz_context *ctx, pdf_annot *annot, fz_buffer *buf, fz_rect *rect)
{
	pdf_obj *line, *le;
	fz_point a, b;
	float w;
	int sc;
	int ic;

	w = pdf_write_border_appearance(ctx, annot, buf);
	sc = pdf_write_stroke_color_appearance(ctx, annot, buf);
	ic = pdf_write_interior_fill_color_appearance(ctx, annot, buf);

	line = pdf_dict_get(ctx, annot->obj, PDF_NAME(L));
	a.x = pdf_array_get_real(ctx, line, 0);
	a.y = pdf_array_get_real(ctx, line, 1);
	b.x = pdf_array_get_real(ctx, line, 2);
	b.y = pdf_array_get_real(ctx, line, 3);

	fz_append_printf(ctx, buf, "%g %g m\n%g %g l\n", a.x, a.y, b.x, b.y);
	maybe_stroke(ctx, buf, sc);

	rect->x0 = fz_min(a.x, b.x);
	rect->y0 = fz_min(a.y, b.y);
	rect->x1 = fz_max(a.x, b.x);
	rect->y1 = fz_max(a.y, b.y);

	le = pdf_dict_get(ctx, annot->obj, PDF_NAME(LE));
	if (pdf_array_len(ctx, le) == 2)
	{
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float l = sqrtf(dx*dx + dy*dy);
		pdf_write_line_cap_appearance(ctx, buf, rect, a.x, a.y, dx/l, dy/l, w, sc, ic, pdf_array_get(ctx, le, 0));
		pdf_write_line_cap_appearance(ctx, buf, rect, b.x, b.y, -dx/l, -dy/l, w, sc, ic, pdf_array_get(ctx, le, 1));
	}
	*rect = fz_expand_rect(*rect, fz_max(1, w));
}