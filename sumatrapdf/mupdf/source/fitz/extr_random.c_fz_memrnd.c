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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ fz_lrand48 (int /*<<< orphan*/ *) ; 

void fz_memrnd(fz_context *ctx, unsigned char *data, int len)
{
	while (len-- > 0)
		*data++ = (unsigned char)fz_lrand48(ctx);
}