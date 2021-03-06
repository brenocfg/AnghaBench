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
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,float,float) ; 

__attribute__((used)) static void
svg_path_moveto(fz_context *ctx, void *arg, float x, float y)
{
	fz_output *out = (fz_output *)arg;

	fz_write_printf(ctx, out, "M %g %g ", x, y);
}