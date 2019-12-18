#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ font; } ;
struct TYPE_5__ {int /*<<< orphan*/  stroke_state; scalar_t__ softmask_resources; scalar_t__ softmask; TYPE_1__ text; int /*<<< orphan*/  fill; int /*<<< orphan*/  stroke; } ;
typedef  TYPE_2__ pdf_gstate ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_keep_stroke_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_keep_font (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pdf_keep_material (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_keep_obj (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
pdf_keep_gstate(fz_context *ctx, pdf_gstate *gs)
{
	pdf_keep_material(ctx, &gs->stroke);
	pdf_keep_material(ctx, &gs->fill);
	if (gs->text.font)
		pdf_keep_font(ctx, gs->text.font);
	if (gs->softmask)
		pdf_keep_obj(ctx, gs->softmask);
	if (gs->softmask_resources)
		pdf_keep_obj(ctx, gs->softmask_resources);
	fz_keep_stroke_state(ctx, gs->stroke_state);
}