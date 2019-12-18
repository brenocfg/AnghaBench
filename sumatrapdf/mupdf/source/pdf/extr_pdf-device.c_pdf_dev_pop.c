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
struct TYPE_9__ {size_t num_gstates; TYPE_1__* gstates; } ;
typedef  TYPE_2__ pdf_device ;
struct TYPE_10__ {int /*<<< orphan*/  (* on_pop ) (int /*<<< orphan*/ *,TYPE_2__*,void*) ;int /*<<< orphan*/  buf; void* on_pop_arg; } ;
typedef  TYPE_3__ gstate ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  stroke_state; } ;

/* Variables and functions */
 TYPE_3__* CURRENT_GSTATE (TYPE_2__*) ; 
 int /*<<< orphan*/  fz_append_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_drop_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_stroke_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*,void*) ; 

__attribute__((used)) static void *
pdf_dev_pop(fz_context *ctx, pdf_device *pdev)
{
	gstate *gs = CURRENT_GSTATE(pdev);
	void *arg = gs->on_pop_arg;

	fz_append_string(ctx, gs->buf, "Q\n");
	if (gs->on_pop)
		gs->on_pop(ctx, pdev, arg);
	pdev->num_gstates--;
	fz_drop_stroke_state(ctx, pdev->gstates[pdev->num_gstates].stroke_state);
	fz_drop_buffer(ctx, pdev->gstates[pdev->num_gstates].buf);
	return arg;
}