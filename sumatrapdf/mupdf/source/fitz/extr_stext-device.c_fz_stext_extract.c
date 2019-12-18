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
struct TYPE_12__ {scalar_t__ f; scalar_t__ e; } ;
struct TYPE_11__ {int len; int /*<<< orphan*/  wmode; TYPE_1__* items; TYPE_3__ trm; int /*<<< orphan*/ * font; } ;
typedef  TYPE_2__ fz_text_span ;
typedef  int /*<<< orphan*/  fz_stext_device ;
typedef  TYPE_3__ fz_matrix ;
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_10__ {scalar_t__ gid; int /*<<< orphan*/  ucs; scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_add_stext_char (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,TYPE_3__,float,int /*<<< orphan*/ ) ; 
 float fz_advance_glyph (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__ fz_concat (TYPE_3__,TYPE_3__) ; 

__attribute__((used)) static void
fz_stext_extract(fz_context *ctx, fz_stext_device *dev, fz_text_span *span, fz_matrix ctm)
{
	fz_font *font = span->font;
	fz_matrix tm = span->trm;
	fz_matrix trm;
	float adv;
	int i;

	if (span->len == 0)
		return;

	tm.e = 0;
	tm.f = 0;
	trm = fz_concat(tm, ctm);

	for (i = 0; i < span->len; i++)
	{
		/* Calculate new pen location and delta */
		tm.e = span->items[i].x;
		tm.f = span->items[i].y;
		trm = fz_concat(tm, ctm);

		/* Calculate bounding box and new pen position based on font metrics */
		if (span->items[i].gid >= 0)
			adv = fz_advance_glyph(ctx, font, span->items[i].gid, span->wmode);
		else
			adv = 0;

		fz_add_stext_char(ctx, dev, font, span->items[i].ucs, span->items[i].gid, trm, adv, span->wmode);
	}
}