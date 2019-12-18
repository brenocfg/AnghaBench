#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* op_END ) (int /*<<< orphan*/ *,TYPE_1__*) ;} ;
typedef  TYPE_1__ pdf_processor ;
struct TYPE_9__ {scalar_t__ gstate; } ;
typedef  TYPE_2__ pdf_csi ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_process_grestore (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
pdf_process_end(fz_context *ctx, pdf_processor *proc, pdf_csi *csi)
{
	while (csi->gstate > 0)
		pdf_process_grestore(ctx, proc, csi);
	if (proc->op_END)
		proc->op_END(ctx, proc);
}