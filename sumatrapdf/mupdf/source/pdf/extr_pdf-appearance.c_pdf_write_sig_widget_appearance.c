#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_annot ;
struct TYPE_4__ {int x0; int y0; int x1; int y1; } ;
typedef  TYPE_1__ fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fz_identity ; 

__attribute__((used)) static void
pdf_write_sig_widget_appearance(fz_context *ctx, pdf_annot *annot, fz_buffer *buf,
	fz_rect *rect, fz_rect *bbox, fz_matrix *matrix, pdf_obj **res)
{
	float x0 = rect->x0 + 1;
	float y0 = rect->y0 + 1;
	float x1 = rect->x1 - 1;
	float y1 = rect->y1 - 1;
	float w = x1 - x0;
	float h = y1 - y0;
	fz_append_printf(ctx, buf, "1 w\n0 G\n");
	fz_append_printf(ctx, buf, "%g %g %g %g re\n", x0, y0, w, h);
	fz_append_printf(ctx, buf, "%g %g m %g %g l\n", x0, y0, x1, y1);
	fz_append_printf(ctx, buf, "%g %g m %g %g l\n", x1, y0, x0, y1);
	fz_append_printf(ctx, buf, "s\n");
	*bbox = *rect;
	*matrix = fz_identity;
}