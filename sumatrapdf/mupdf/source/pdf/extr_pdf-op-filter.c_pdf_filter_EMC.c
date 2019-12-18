#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_processor ;
struct TYPE_7__ {TYPE_3__* chain; TYPE_5__* current_tags; TYPE_5__* pending_tags; } ;
typedef  TYPE_1__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_9__ {int /*<<< orphan*/  raw; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* op_EMC ) (int /*<<< orphan*/ *,TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Properties ; 
 int /*<<< orphan*/  copy_resource (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_to_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop_tag (int /*<<< orphan*/ *,TYPE_1__*,TYPE_5__**) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  update_mcid (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
pdf_filter_EMC(fz_context *ctx, pdf_processor *proc)
{
	pdf_filter_processor *p = (pdf_filter_processor*)proc;

	/* If we have any pending tags, pop one of those. If not,
	 * pop one of the current ones, and pass the EMC on. */
	if (p->pending_tags != NULL)
		pop_tag(ctx, p, &p->pending_tags);
	else if (p->current_tags)
	{
		update_mcid(ctx, p);
		copy_resource(ctx, p, PDF_NAME(Properties), pdf_to_name(ctx, p->current_tags->raw));
		pop_tag(ctx, p, &p->current_tags);
		if (p->chain->op_EMC)
			p->chain->op_EMC(ctx, p->chain);
	}
}