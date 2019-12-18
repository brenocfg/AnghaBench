#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  doc ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  out ; 
 int /*<<< orphan*/  pdf_print_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pdf_trailer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tight ; 

__attribute__((used)) static void showtrailer(void)
{
	if (tight)
		fz_write_printf(ctx, out, "trailer ");
	else
		fz_write_printf(ctx, out, "trailer\n");
	pdf_print_obj(ctx, out, pdf_trailer(ctx, doc), tight, 1);
	fz_write_printf(ctx, out, "\n");
}