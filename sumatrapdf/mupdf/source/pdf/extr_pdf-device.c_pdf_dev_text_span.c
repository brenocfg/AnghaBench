#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_device ;
struct TYPE_19__ {int font_size; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ gstate ;
struct TYPE_23__ {int e; int f; } ;
struct TYPE_20__ {int len; int wmode; int /*<<< orphan*/  font; TYPE_3__* items; TYPE_5__ trm; } ;
typedef  TYPE_2__ fz_text_span ;
struct TYPE_21__ {int x; int y; int gid; } ;
typedef  TYPE_3__ fz_text_item ;
struct TYPE_22__ {int x; int y; } ;
typedef  TYPE_4__ fz_point ;
typedef  TYPE_5__ fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* CURRENT_GSTATE (int /*<<< orphan*/ *) ; 
 float fz_advance_glyph (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fz_append_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_5__ fz_concat (TYPE_5__,TYPE_5__) ; 
 scalar_t__ fz_font_t3_procs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__ fz_invert_matrix (TYPE_5__) ; 
 TYPE_5__ fz_pre_translate (TYPE_5__,float,float) ; 
 TYPE_5__ fz_scale (int,int) ; 
 TYPE_4__ fz_transform_vector (TYPE_4__,TYPE_5__) ; 

__attribute__((used)) static void
pdf_dev_text_span(fz_context *ctx, pdf_device *pdev, fz_text_span *span)
{
	gstate *gs = CURRENT_GSTATE(pdev);
	fz_matrix trm, tm, tlm, inv_trm, inv_tm;
	fz_matrix inv_tfs;
	fz_point d;
	float adv;
	int dx, dy;
	int i;

	if (span->len == 0)
		return;

	inv_tfs = fz_scale(1 / gs->font_size, 1 / gs->font_size);

	trm = span->trm;
	trm.e = span->items[0].x;
	trm.f = span->items[0].y;

	tm = fz_concat(inv_tfs, trm);
	tlm = tm;

	inv_tm = fz_invert_matrix(tm);
	inv_trm = fz_invert_matrix(trm);

	fz_append_printf(ctx, gs->buf, "%M Tm\n[<", &tm);

	for (i = 0; i < span->len; ++i)
	{
		fz_text_item *it = &span->items[i];
		if (it->gid < 0)
			continue;

		/* transform difference from expected pen position into font units. */
		d.x = it->x - trm.e;
		d.y = it->y - trm.f;
		d = fz_transform_vector(d, inv_trm);
		dx = (int)(d.x * 1000 + (d.x < 0 ? -0.5f : 0.5f));
		dy = (int)(d.y * 1000 + (d.y < 0 ? -0.5f : 0.5f));

		trm.e = it->x;
		trm.f = it->y;

		if (dx != 0 || dy != 0)
		{
			if (span->wmode == 0 && dy == 0)
				fz_append_printf(ctx, gs->buf, ">%d<", -dx);
			else if (span->wmode == 1 && dx == 0)
				fz_append_printf(ctx, gs->buf, ">%d<", -dy);
			else
			{
				/* Calculate offset from start of the previous line */
				tm = fz_concat(inv_tfs, trm);
				d.x = tm.e - tlm.e;
				d.y = tm.f - tlm.f;
				d = fz_transform_vector(d, inv_tm);
				fz_append_printf(ctx, gs->buf, ">]TJ\n%g %g Td\n[<", d.x, d.y);
				tlm = tm;
			}
		}

		if (fz_font_t3_procs(ctx, span->font))
			fz_append_printf(ctx, gs->buf, "%02x", it->gid);
		else
			fz_append_printf(ctx, gs->buf, "%04x", it->gid);

		adv = fz_advance_glyph(ctx, span->font, it->gid, span->wmode);
		if (span->wmode == 0)
			trm = fz_pre_translate(trm, adv, 0);
		else
			trm = fz_pre_translate(trm, 0, adv);
	}

	fz_append_string(ctx, gs->buf, ">]TJ\n");
}