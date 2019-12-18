#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_14__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
struct TYPE_15__ {void* y1; void* y0; void* x1; void* x0; } ;
typedef  TYPE_2__ fz_rect ;
struct TYPE_16__ {void* y; void* x; } ;
typedef  TYPE_3__ fz_point ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vertices ; 
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,void*,void*) ; 
 int /*<<< orphan*/  fz_append_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ fz_empty_rect ; 
 TYPE_2__ fz_expand_rect (TYPE_2__,float) ; 
 TYPE_2__ fz_include_point_in_rect (TYPE_2__,TYPE_3__) ; 
 int /*<<< orphan*/  maybe_stroke (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* pdf_array_get_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float pdf_write_border_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int pdf_write_stroke_color_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pdf_write_polygon_appearance(fz_context *ctx, pdf_annot *annot, fz_buffer *buf, fz_rect *rect, int close)
{
	pdf_obj *verts;
	fz_point p;
	int i, n;
	float lw;
	int sc;

	lw = pdf_write_border_appearance(ctx, annot, buf);
	sc = pdf_write_stroke_color_appearance(ctx, annot, buf);

	*rect = fz_empty_rect;

	verts = pdf_dict_get(ctx, annot->obj, PDF_NAME(Vertices));
	n = pdf_array_len(ctx, verts) / 2;
	if (n > 0)
	{
		for (i = 0; i < n; ++i)
		{
			p.x = pdf_array_get_real(ctx, verts, i*2+0);
			p.y = pdf_array_get_real(ctx, verts, i*2+1);
			if (i == 0)
			{
				rect->x0 = rect->x1 = p.x;
				rect->y0 = rect->y1 = p.y;
			}
			else
				*rect = fz_include_point_in_rect(*rect, p);
			if (i == 0)
				fz_append_printf(ctx, buf, "%g %g m\n", p.x, p.y);
			else
				fz_append_printf(ctx, buf, "%g %g l\n", p.x, p.y);
		}
		if (close)
			fz_append_string(ctx, buf, "h\n");
		maybe_stroke(ctx, buf, sc);
		*rect = fz_expand_rect(*rect, lw);
	}
}