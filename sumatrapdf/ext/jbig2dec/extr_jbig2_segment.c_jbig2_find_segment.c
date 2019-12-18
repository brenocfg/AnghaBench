#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {int segment_index; TYPE_1__** segments; struct TYPE_6__* global_ctx; } ;
struct TYPE_5__ {scalar_t__ number; } ;
typedef  TYPE_1__ Jbig2Segment ;
typedef  TYPE_2__ Jbig2Ctx ;

/* Variables and functions */

Jbig2Segment *
jbig2_find_segment(Jbig2Ctx *ctx, uint32_t number)
{
    int index, index_max = ctx->segment_index - 1;
    const Jbig2Ctx *global_ctx = ctx->global_ctx;

    /* FIXME: binary search would be better */
    for (index = index_max; index >= 0; index--)
        if (ctx->segments[index]->number == number)
            return (ctx->segments[index]);

    if (global_ctx)
        for (index = global_ctx->segment_index - 1; index >= 0; index--)
            if (global_ctx->segments[index]->number == number)
                return (global_ctx->segments[index]);

    /* didn't find a match */
    return NULL;
}