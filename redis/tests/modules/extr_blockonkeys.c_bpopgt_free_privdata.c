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
typedef  void RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_NOT_USED (void*) ; 

void bpopgt_free_privdata(RedisModuleCtx *ctx, void *privdata) {
    /* Nothing to do because privdata is actually a 'long long',
     * not a pointer to the heap */
    REDISMODULE_NOT_USED(ctx);
    REDISMODULE_NOT_USED(privdata);
}