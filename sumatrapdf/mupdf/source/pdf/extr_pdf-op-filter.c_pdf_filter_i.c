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
struct TYPE_5__ {int /*<<< orphan*/  (* op_i ) (int /*<<< orphan*/ *,TYPE_2__*,float) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  filter_flush (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*,float) ; 

__attribute__((used)) static void
pdf_filter_i(fz_context *ctx, pdf_processor *proc, float flatness)
{
	pdf_filter_processor *p = (pdf_filter_processor*)proc;
	filter_flush(ctx, p, 0);
	if (p->chain->op_i)
		p->chain->op_i(ctx, p->chain, flatness);
}