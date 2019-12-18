#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ hidden; int /*<<< orphan*/  usage; int /*<<< orphan*/  (* op_BDC ) (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ pdf_processor ;
struct TYPE_10__ {int /*<<< orphan*/  obj; int /*<<< orphan*/  rdb; TYPE_1__* doc; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ pdf_csi ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {int /*<<< orphan*/  ocg; } ;

/* Variables and functions */
 scalar_t__ pdf_is_hidden_ocg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_properties (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pdf_process_BDC(fz_context *ctx, pdf_processor *proc, pdf_csi *csi)
{
	if (proc->op_BDC)
		proc->op_BDC(ctx, proc, csi->name, csi->obj, resolve_properties(ctx, csi, csi->obj));

	/* Already hidden, no need to look further */
	if (proc->hidden > 0)
	{
		++proc->hidden;
		return;
	}

	/* We only look at OC groups here */
	if (strcmp(csi->name, "OC"))
		return;

	if (pdf_is_hidden_ocg(ctx, csi->doc->ocg, csi->rdb, proc->usage, csi->obj))
		++proc->hidden;
}