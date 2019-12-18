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
 int /*<<< orphan*/  fz_write_int16_le (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
fz_write_uint16_le(fz_context *ctx, fz_output *out, unsigned int x)
{
	fz_write_int16_le(ctx, out, (int)x);
}