#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int* seed48; } ;
typedef  TYPE_1__ fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_srand48 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fz_init_random_context(fz_context *ctx)
{
	if (!ctx)
		return;

	ctx->seed48[0] = 0;
	ctx->seed48[1] = 0;
	ctx->seed48[2] = 0;
	ctx->seed48[3] = 0xe66d;
	ctx->seed48[4] = 0xdeec;
	ctx->seed48[5] = 0x5;
	ctx->seed48[6] = 0xb;

	fz_srand48(ctx, (uint32_t)time(NULL));
}