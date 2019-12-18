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
typedef  int /*<<< orphan*/  pdf_obj ;

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  out ; 
 scalar_t__ pdf_is_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_print_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * pdf_resolve_indirect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pdf_to_num (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ showbinary ; 
 int /*<<< orphan*/  showstream (int) ; 
 scalar_t__ tight ; 

__attribute__((used)) static void showobject(pdf_obj *ref)
{
	pdf_obj *obj = pdf_resolve_indirect(ctx, ref);
	int num = pdf_to_num(ctx, ref);
	if (pdf_is_stream(ctx, ref))
	{
		if (showbinary)
		{
			showstream(num);
		}
		else
		{
			if (tight)
			{
				fz_write_printf(ctx, out, "%d 0 obj ", num);
				pdf_print_obj(ctx, out, obj, 1, 1);
				fz_write_printf(ctx, out, " stream\n");
			}
			else
			{
				fz_write_printf(ctx, out, "%d 0 obj\n", num);
				pdf_print_obj(ctx, out, obj, 0, 1);
				fz_write_printf(ctx, out, "\nstream\n");
				showstream(num);
				fz_write_printf(ctx, out, "endstream\n");
				fz_write_printf(ctx, out, "endobj\n");
			}
		}
	}
	else
	{
		if (tight)
		{
			fz_write_printf(ctx, out, "%d 0 obj ", num);
			pdf_print_obj(ctx, out, obj, 1, 1);
			fz_write_printf(ctx, out, "\n");
		}
		else
		{
			fz_write_printf(ctx, out, "%d 0 obj\n", num);
			pdf_print_obj(ctx, out, obj, 0, 1);
			fz_write_printf(ctx, out, "\nendobj\n");
		}
	}
}