#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_processor ;
struct TYPE_13__ {TYPE_5__* chain; int /*<<< orphan*/  doc; int /*<<< orphan*/  opaque; int /*<<< orphan*/  (* after_text ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ;TYPE_3__* gstate; scalar_t__ BT_pending; } ;
typedef  TYPE_4__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_14__ {int /*<<< orphan*/  (* op_Q ) (int /*<<< orphan*/ *,TYPE_5__*) ;int /*<<< orphan*/  (* op_q ) (int /*<<< orphan*/ *,TYPE_5__*) ;int /*<<< orphan*/  (* op_ET ) (int /*<<< orphan*/ *,TYPE_5__*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  ctm; } ;
struct TYPE_10__ {int /*<<< orphan*/  ctm; } ;
struct TYPE_12__ {TYPE_2__ sent; TYPE_1__ pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  filter_flush (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static void
pdf_filter_ET(fz_context *ctx, pdf_processor *proc)
{
	pdf_filter_processor *p = (pdf_filter_processor*)proc;

	if (!p->BT_pending)
	{
		filter_flush(ctx, p, 0);
		if (p->chain->op_ET)
			p->chain->op_ET(ctx, p->chain);
	}
	p->BT_pending = 0;
	if (p->after_text)
	{
		fz_matrix ctm = fz_concat(p->gstate->pending.ctm, p->gstate->sent.ctm);
		if (p->chain->op_q)
			p->chain->op_q(ctx, p->chain);
		p->after_text(ctx, p->opaque, p->doc, p->chain, ctm);
		if (p->chain->op_Q)
			p->chain->op_Q(ctx, p->chain);
	}
}