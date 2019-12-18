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
typedef  int /*<<< orphan*/  fz_output ;
struct TYPE_4__ {int /*<<< orphan*/  (* output_accelerator ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_drop_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

void fz_output_accelerator(fz_context *ctx, fz_document *doc, fz_output *accel)
{
	if (doc == NULL || accel == NULL)
		return;
	if (doc->output_accelerator == NULL)
	{
		fz_drop_output(ctx, accel);
		fz_throw(ctx, FZ_ERROR_GENERIC, "Document does not support writing an accelerator");
	}

	doc->output_accelerator(ctx, doc, accel);
}