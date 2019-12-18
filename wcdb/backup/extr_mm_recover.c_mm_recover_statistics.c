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
struct TYPE_3__ {unsigned int succ_count; unsigned int fail_count; } ;
typedef  TYPE_1__ mm_recover_ctx ;

/* Variables and functions */

void mm_recover_statistics(mm_recover_ctx *ctx,
                           unsigned int *succeed,
                           unsigned int *failed)
{
    if (succeed)
        *succeed = ctx->succ_count;
    if (failed)
        *failed = ctx->fail_count;
}