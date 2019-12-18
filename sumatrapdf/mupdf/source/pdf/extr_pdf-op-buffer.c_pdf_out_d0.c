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
struct TYPE_2__ {int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ pdf_output_processor ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,float,float) ; 

__attribute__((used)) static void
pdf_out_d0(fz_context *ctx, pdf_processor *proc, float wx, float wy)
{
	fz_output *out = ((pdf_output_processor*)proc)->out;
	fz_write_printf(ctx, out, "%g %g d0\n", wx, wy);
}