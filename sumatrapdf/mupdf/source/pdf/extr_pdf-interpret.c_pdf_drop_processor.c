#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* drop_processor ) (int /*<<< orphan*/ *,TYPE_1__*) ;scalar_t__ close_processor; } ;
typedef  TYPE_1__ pdf_processor ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
pdf_drop_processor(fz_context *ctx, pdf_processor *proc)
{
	if (proc)
	{
		if (proc->close_processor)
			fz_warn(ctx, "dropping unclosed PDF processor");
		if (proc->drop_processor)
			proc->drop_processor(ctx, proc);
	}
	fz_free(ctx, proc);
}