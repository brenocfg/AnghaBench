#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  font; } ;
struct TYPE_6__ {int /*<<< orphan*/  stroke_state; int /*<<< orphan*/  softmask; TYPE_1__ text; int /*<<< orphan*/  ctm; } ;
typedef  TYPE_2__ pdf_gstate ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_stroke_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_keep_stroke_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_drop_font (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_keep_font (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_keep_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pdf_copy_pattern_gstate(fz_context *ctx, pdf_gstate *dst, const pdf_gstate *src)
{
	dst->ctm = src->ctm;

	pdf_drop_font(ctx, dst->text.font);
	dst->text.font = pdf_keep_font(ctx, src->text.font);

	pdf_drop_obj(ctx, dst->softmask);
	dst->softmask = pdf_keep_obj(ctx, src->softmask);

	fz_drop_stroke_state(ctx, dst->stroke_state);
	dst->stroke_state = fz_keep_stroke_state(ctx, src->stroke_state);
}