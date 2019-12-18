#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_processor ;
struct TYPE_2__ {int ahxencode; int /*<<< orphan*/  extgstate; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ pdf_output_processor ;
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,float) ; 
 int /*<<< orphan*/  pdf_print_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
pdf_out_d(fz_context *ctx, pdf_processor *proc, pdf_obj *array, float phase)
{
	fz_output *out = ((pdf_output_processor*)proc)->out;
	int ahx = ((pdf_output_processor*)proc)->ahxencode;
	if (!((pdf_output_processor*)proc)->extgstate)
	{
		pdf_print_obj(ctx, out, array, 1, ahx);
		fz_write_printf(ctx, out, " %g d\n", phase);
	}
}