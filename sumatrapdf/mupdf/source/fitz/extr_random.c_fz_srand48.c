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
typedef  int uint16_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_seed48 (int /*<<< orphan*/ *,int*) ; 

void fz_srand48(fz_context *ctx, int32_t seed)
{
	uint16_t p[3] = { 0x330e, seed, seed>>16 };
	fz_seed48(ctx, p);
}