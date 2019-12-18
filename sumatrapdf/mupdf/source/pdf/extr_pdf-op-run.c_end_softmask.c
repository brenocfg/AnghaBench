#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * page_resources; int /*<<< orphan*/ * softmask; int /*<<< orphan*/  ctm; } ;
typedef  TYPE_1__ softmask_save ;
struct TYPE_7__ {int gtop; int /*<<< orphan*/  dev; TYPE_3__* gstate; } ;
typedef  TYPE_2__ pdf_run_processor ;
struct TYPE_8__ {int /*<<< orphan*/  softmask_ctm; int /*<<< orphan*/ * softmask_resources; int /*<<< orphan*/ * softmask; } ;
typedef  TYPE_3__ pdf_gstate ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_pop_clip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
end_softmask(fz_context *ctx, pdf_run_processor *pr, softmask_save *save)
{
	pdf_gstate *gstate = pr->gstate + pr->gtop;

	if (save->softmask == NULL)
		return;

	gstate->softmask = save->softmask;
	gstate->softmask_resources = save->page_resources;
	gstate->softmask_ctm = save->ctm;
	save->softmask = NULL;
	save->page_resources = NULL;

	fz_pop_clip(ctx, pr->dev);
}