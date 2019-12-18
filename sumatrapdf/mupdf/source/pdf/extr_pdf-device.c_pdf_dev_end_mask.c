#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
struct TYPE_6__ {int /*<<< orphan*/ * doc; } ;
typedef  TYPE_1__ pdf_device ;
struct TYPE_7__ {int /*<<< orphan*/  buf; int /*<<< orphan*/ * on_pop_arg; } ;
typedef  TYPE_2__ gstate ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_2__* CURRENT_GSTATE (TYPE_1__*) ; 
 int /*<<< orphan*/  fz_append_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_drop_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_keep_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dev_end_text (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_update_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pdf_dev_end_mask(fz_context *ctx, fz_device *dev)
{
	pdf_device *pdev = (pdf_device*)dev;
	pdf_document *doc = pdev->doc;
	gstate *gs = CURRENT_GSTATE(pdev);
	pdf_obj *form_ref = (pdf_obj *)gs->on_pop_arg;

	/* Here we do part of the pop, but not all of it. */
	pdf_dev_end_text(ctx, pdev);
	fz_append_string(ctx, gs->buf, "Q\n");
	pdf_update_stream(ctx, doc, form_ref, gs->buf, 0);
	fz_drop_buffer(ctx, gs->buf);
	gs->buf = fz_keep_buffer(ctx, gs[-1].buf);
	gs->on_pop_arg = NULL;
	pdf_drop_obj(ctx, form_ref);
	fz_append_string(ctx, gs->buf, "q\n");
}