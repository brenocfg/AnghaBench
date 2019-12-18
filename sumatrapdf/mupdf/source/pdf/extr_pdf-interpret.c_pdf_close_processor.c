#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* close_processor ) (int /*<<< orphan*/ *,TYPE_1__*) ;} ;
typedef  TYPE_1__ pdf_processor ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
pdf_close_processor(fz_context *ctx, pdf_processor *proc)
{
	if (proc && proc->close_processor)
	{
		proc->close_processor(ctx, proc);
		proc->close_processor = NULL;
	}
}