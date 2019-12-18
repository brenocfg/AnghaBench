#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_10__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_rect ;
struct TYPE_11__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ fz_point ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 size_t LL ; 
 size_t LR ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QuadPoints ; 
 size_t UL ; 
 size_t UR ; 
 float extract_quad (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fz_empty_rect ; 
 TYPE_2__ lerp_point (TYPE_2__,TYPE_2__,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_write_stroke_color_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  union_quad (int /*<<< orphan*/ *,TYPE_2__*,float) ; 

__attribute__((used)) static void
pdf_write_strike_out_appearance(fz_context *ctx, pdf_annot *annot, fz_buffer *buf, fz_rect *rect)
{
	fz_point quad[4], a, b;
	float h;
	pdf_obj *qp;
	int i, n;

	pdf_write_stroke_color_appearance(ctx, annot, buf);

	qp = pdf_dict_get(ctx, annot->obj, PDF_NAME(QuadPoints));
	n = pdf_array_len(ctx, qp);
	if (n > 0)
	{
		*rect = fz_empty_rect;
		for (i = 0; i < n; i += 8)
		{
			/* Acrobat draws the line at 3/7 of the box width from the bottom
			 * of the box and 1/16 thick of the box width. */

			h = extract_quad(ctx, quad, qp, i);
			a = lerp_point(quad[LL], quad[UL], 3/7.0f);
			b = lerp_point(quad[LR], quad[UR], 3/7.0f);

			fz_append_printf(ctx, buf, "%g w\n", h/16);
			fz_append_printf(ctx, buf, "%g %g m\n", a.x, a.y);
			fz_append_printf(ctx, buf, "%g %g l\n", b.x, b.y);
			fz_append_printf(ctx, buf, "S\n");

			union_quad(rect, quad, h/16);
		}
	}
}