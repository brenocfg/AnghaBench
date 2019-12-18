#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_device ;
struct TYPE_3__ {int text_rendering_mode; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ gstate ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* CURRENT_GSTATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
pdf_dev_trm(fz_context *ctx, pdf_device *pdev, int trm)
{
	gstate *gs = CURRENT_GSTATE(pdev);

	if (gs->text_rendering_mode == trm)
		return;
	gs->text_rendering_mode = trm;
	fz_append_printf(ctx, gs->buf, "%d Tr\n", trm);
}