#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_6__* gstate; TYPE_7__* chain; } ;
typedef  TYPE_5__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_12__ {int /*<<< orphan*/  font; } ;
struct TYPE_13__ {TYPE_3__ text; } ;
struct TYPE_10__ {int /*<<< orphan*/  font; } ;
struct TYPE_11__ {TYPE_1__ text; } ;
struct TYPE_15__ {TYPE_4__ sent; TYPE_2__ pending; scalar_t__ pushed; struct TYPE_15__* next; } ;
typedef  TYPE_6__ filter_gstate ;
struct TYPE_16__ {int /*<<< orphan*/  (* op_Q ) (int /*<<< orphan*/ *,TYPE_7__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  pdf_drop_font (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_7__*) ; 

__attribute__((used)) static int
filter_pop(fz_context *ctx, pdf_filter_processor *p)
{
	filter_gstate *gstate = p->gstate;
	filter_gstate *old = gstate->next;

	/* We are at the top, so nothing to pop! */
	if (old == NULL)
		return 1;

	if (gstate->pushed)
		if (p->chain->op_Q)
			p->chain->op_Q(ctx, p->chain);

	pdf_drop_font(ctx, gstate->pending.text.font);
	pdf_drop_font(ctx, gstate->sent.text.font);
	fz_free(ctx, gstate);
	p->gstate = old;
	return 0;
}