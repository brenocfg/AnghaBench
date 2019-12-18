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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  seed48; } ;
typedef  TYPE_1__ fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_nrand48 (TYPE_1__*,int /*<<< orphan*/ ) ; 

int32_t fz_lrand48(fz_context *ctx)
{
	return fz_nrand48(ctx, ctx->seed48);
}