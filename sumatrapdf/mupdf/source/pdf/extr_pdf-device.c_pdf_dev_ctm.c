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
struct TYPE_3__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  ctm; } ;
typedef  TYPE_1__ gstate ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  ctm ;

/* Variables and functions */
 TYPE_1__* CURRENT_GSTATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_invert_matrix (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
pdf_dev_ctm(fz_context *ctx, pdf_device *pdev, fz_matrix ctm)
{
	fz_matrix inverse;
	gstate *gs = CURRENT_GSTATE(pdev);

	if (memcmp(&gs->ctm, &ctm, sizeof(ctm)) == 0)
		return;
	inverse = fz_invert_matrix(gs->ctm);
	inverse = fz_concat(ctm, inverse);
	gs->ctm = ctm;
	fz_append_printf(ctx, gs->buf, "%M cm\n", &inverse);
}