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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  seed48; } ;
typedef  TYPE_1__ fz_context ;

/* Variables and functions */
 int fz_rand48_step (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

double fz_erand48(fz_context *ctx, uint16_t s[3])
{
	union {
		uint64_t u;
		double f;
	} x = { 0x3ff0000000000000ULL | fz_rand48_step(s, ctx->seed48+3)<<4 };
	return x.f - 1.0;
}