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
struct TYPE_7__ {TYPE_2__* gstate; TYPE_3__* chain; } ;
typedef  TYPE_1__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {int pushed; int /*<<< orphan*/ * next; } ;
typedef  TYPE_2__ filter_gstate ;
struct TYPE_9__ {int /*<<< orphan*/  (* op_q ) (int /*<<< orphan*/ *,TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  filter_push (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static filter_gstate *
gstate_to_update(fz_context *ctx, pdf_filter_processor *p)
{
	filter_gstate *gstate = p->gstate;

	/* If we're not the top, that's fine */
	if (gstate->next != NULL)
		return gstate;

	/* We are the top. Push a group, so we're not */
	filter_push(ctx, p);
	gstate = p->gstate;
	gstate->pushed = 1;
	if (p->chain->op_q)
		p->chain->op_q(ctx, p->chain);

	return p->gstate;
}