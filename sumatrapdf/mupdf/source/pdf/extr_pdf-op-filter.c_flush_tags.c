#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* prev; int /*<<< orphan*/  tag; int /*<<< orphan*/  cooked; int /*<<< orphan*/  raw; scalar_t__ bdc; } ;
typedef  TYPE_1__ tag_record ;
struct TYPE_8__ {TYPE_1__* current_tags; TYPE_3__* chain; } ;
typedef  TYPE_2__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_9__ {int /*<<< orphan*/  (* op_BMC ) (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* op_BDC ) (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flush_tags(fz_context *ctx, pdf_filter_processor *p, tag_record **tags)
{
	tag_record *tag = *tags;

	if (tag == NULL)
		return;
	if (tag->prev)
		flush_tags(ctx, p, &tag->prev);
	if (tag->bdc)
	{
		if (p->chain->op_BDC)
			p->chain->op_BDC(ctx, p->chain, tag->tag, tag->raw, tag->cooked);
	}
	else if (p->chain->op_BMC)
		p->chain->op_BMC(ctx, p->chain, tag->tag);
	tag->prev = p->current_tags;
	p->current_tags = tag;
	*tags = NULL;
}