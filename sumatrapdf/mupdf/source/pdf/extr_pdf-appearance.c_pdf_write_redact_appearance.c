#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_10__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
struct TYPE_11__ {scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; scalar_t__ y0; } ;
typedef  TYPE_2__ fz_rect ;
struct TYPE_12__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ fz_point ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 size_t LL ; 
 size_t LR ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QuadPoints ; 
 size_t UL ; 
 size_t UR ; 
 int /*<<< orphan*/  extract_quad (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 TYPE_2__ fz_empty_rect ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  union_quad (TYPE_2__*,TYPE_3__*,int) ; 

__attribute__((used)) static void
pdf_write_redact_appearance(fz_context *ctx, pdf_annot *annot, fz_buffer *buf, fz_rect *rect)
{
	fz_point quad[4];
	pdf_obj *qp;
	int i, n;

	fz_append_printf(ctx, buf, "1 0 0 RG\n");

	qp = pdf_dict_get(ctx, annot->obj, PDF_NAME(QuadPoints));
	n = pdf_array_len(ctx, qp);
	if (n > 0)
	{
		*rect = fz_empty_rect;
		for (i = 0; i < n; i += 8)
		{
			extract_quad(ctx, quad, qp, i);
			fz_append_printf(ctx, buf, "%g %g m\n", quad[LL].x, quad[LL].y);
			fz_append_printf(ctx, buf, "%g %g l\n", quad[LR].x, quad[LR].y);
			fz_append_printf(ctx, buf, "%g %g l\n", quad[UR].x, quad[UR].y);
			fz_append_printf(ctx, buf, "%g %g l\n", quad[UL].x, quad[UL].y);
			fz_append_printf(ctx, buf, "s\n");
			union_quad(rect, quad, 1);
		}
	}
	else
	{
		fz_append_printf(ctx, buf, "%g %g m\n", rect->x0+1, rect->y0+1);
		fz_append_printf(ctx, buf, "%g %g l\n", rect->x1-1, rect->y0+1);
		fz_append_printf(ctx, buf, "%g %g l\n", rect->x1-1, rect->y1-1);
		fz_append_printf(ctx, buf, "%g %g l\n", rect->x0+1, rect->y1-1);
		fz_append_printf(ctx, buf, "s\n");
	}
}