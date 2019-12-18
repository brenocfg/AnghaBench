#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_processor ;
struct TYPE_9__ {TYPE_5__* chain; int /*<<< orphan*/  Tm_pending; TYPE_3__* gstate; int /*<<< orphan*/  tos; } ;
typedef  TYPE_4__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_10__ {int /*<<< orphan*/  (* op_Tstar ) (int /*<<< orphan*/ *,TYPE_5__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  leading; } ;
struct TYPE_7__ {TYPE_1__ text; } ;
struct TYPE_8__ {TYPE_2__ pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_tos_newline (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static void
pdf_filter_Tstar(fz_context *ctx, pdf_processor *proc)
{
	pdf_filter_processor *p = (pdf_filter_processor*)proc;
	pdf_tos_newline(&p->tos, p->gstate->pending.text.leading);
	/* If Tm_pending, then just adjusting the matrix (as
	 * pdf_tos_newline has done) is enough. Otherwise we
	 * need to actually call the operator. */
	if (!p->Tm_pending && p->chain->op_Tstar)
		p->chain->op_Tstar(ctx, p->chain);
}