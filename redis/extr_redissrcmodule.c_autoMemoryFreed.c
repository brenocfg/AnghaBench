#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int amqueue_used; TYPE_1__* amqueue; } ;
struct TYPE_4__ {int type; void* ptr; } ;
typedef  TYPE_2__ RedisModuleCtx ;

/* Variables and functions */
 int REDISMODULE_AM_FREED ; 
 int REDISMODULE_CTX_AUTO_MEMORY ; 

int autoMemoryFreed(RedisModuleCtx *ctx, int type, void *ptr) {
    if (!(ctx->flags & REDISMODULE_CTX_AUTO_MEMORY)) return 0;

    int count = (ctx->amqueue_used+1)/2;
    for (int j = 0; j < count; j++) {
        for (int side = 0; side < 2; side++) {
            /* For side = 0 check right side of the array, for
             * side = 1 check the left side instead (zig-zag scanning). */
            int i = (side == 0) ? (ctx->amqueue_used - 1 - j) : j;
            if (ctx->amqueue[i].type == type &&
                ctx->amqueue[i].ptr == ptr)
            {
                ctx->amqueue[i].type = REDISMODULE_AM_FREED;

                /* Switch the freed element and the last element, to avoid growing
                 * the queue unnecessarily if we allocate/free in a loop */
                if (i != ctx->amqueue_used-1) {
                    ctx->amqueue[i] = ctx->amqueue[ctx->amqueue_used-1];
                }

                /* Reduce the size of the queue because we either moved the top
                 * element elsewhere or freed it */
                ctx->amqueue_used--;
                return 1;
            }
        }
    }
    return 0;
}