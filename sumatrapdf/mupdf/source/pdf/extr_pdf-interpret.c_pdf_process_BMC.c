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
struct TYPE_4__ {scalar_t__ hidden; int /*<<< orphan*/  (* op_BMC ) (int /*<<< orphan*/ *,TYPE_1__*,char const*) ;} ;
typedef  TYPE_1__ pdf_processor ;
typedef  int /*<<< orphan*/  pdf_csi ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*,char const*) ; 

__attribute__((used)) static void
pdf_process_BMC(fz_context *ctx, pdf_processor *proc, pdf_csi *csi, const char *name)
{
	if (proc->op_BMC)
		proc->op_BMC(ctx, proc, name);
	if (proc->hidden > 0)
		++proc->hidden;
}