#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/ * out; } ;
typedef  TYPE_3__ svg_device ;
struct TYPE_17__ {int /*<<< orphan*/  d; int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct TYPE_20__ {int len; TYPE_5__* items; TYPE_1__ trm; } ;
typedef  TYPE_4__ fz_text_span ;
struct TYPE_21__ {int gid; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_5__ fz_text_item ;
typedef  int /*<<< orphan*/  fz_output ;
struct TYPE_22__ {int member_0; int member_3; scalar_t__ f; scalar_t__ e; int /*<<< orphan*/  d; int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_6__ fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;
struct TYPE_23__ {int /*<<< orphan*/  id; TYPE_2__* sentlist; } ;
typedef  TYPE_7__ font ;
struct TYPE_18__ {scalar_t__ y_off; scalar_t__ x_off; } ;

/* Variables and functions */
 TYPE_6__ fz_concat (TYPE_6__,TYPE_6__) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  svg_dev_ctm (int /*<<< orphan*/ *,TYPE_3__*,TYPE_6__) ; 
 int /*<<< orphan*/  svg_dev_fill_color (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,float const*,float,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
svg_dev_text_span_as_paths_fill(fz_context *ctx, fz_device *dev, const fz_text_span *span, fz_matrix ctm,
	fz_colorspace *colorspace, const float *color, float alpha, font *fnt, fz_color_params color_params)
{
	svg_device *sdev = (svg_device*)dev;
	fz_output *out = sdev->out;
	fz_matrix shift = { 1, 0, 0, 1, 0, 0};
	fz_matrix trm, mtx;
	int i;

	/* Rely on the fact that trm.{e,f} == 0 */
	trm.a = span->trm.a;
	trm.b = span->trm.b;
	trm.c = span->trm.c;
	trm.d = span->trm.d;
	trm.e = 0;
	trm.f = 0;

	for (i=0; i < span->len; i++)
	{
		fz_text_item *it = &span->items[i];
		int gid = it->gid;
		if (gid < 0)
			continue;

		shift.e = fnt->sentlist[gid].x_off;
		shift.f = fnt->sentlist[gid].y_off;
		trm.e = it->x;
		trm.f = it->y;
		mtx = fz_concat(shift, fz_concat(trm, ctm));

		fz_write_printf(ctx, out, "<use xlink:href=\"#font_%x_%x\"", fnt->id, gid);
		svg_dev_ctm(ctx, sdev, mtx);
		svg_dev_fill_color(ctx, sdev, colorspace, color, alpha, color_params);
		fz_write_printf(ctx, out, "/>\n");
	}
}