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
typedef  int /*<<< orphan*/  pdf_processor ;
struct TYPE_4__ {TYPE_2__* chain; } ;
typedef  TYPE_1__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int /*<<< orphan*/  (* op_gs_op ) (int /*<<< orphan*/ *,TYPE_2__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  filter_flush (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

__attribute__((used)) static void
pdf_filter_gs_op(fz_context *ctx, pdf_processor *proc, int b)
{
	pdf_filter_processor *p = (pdf_filter_processor*)proc;
	filter_flush(ctx, p, 0);
	if (p->chain->op_gs_op)
		p->chain->op_gs_op(ctx, p->chain, b);
}