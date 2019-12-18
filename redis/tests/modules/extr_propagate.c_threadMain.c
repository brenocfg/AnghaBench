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
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_NOT_USED (void*) ; 
 int /*<<< orphan*/  RedisModule_FreeThreadSafeContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_GetThreadSafeContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_Replicate (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  RedisModule_SelectDb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RedisModule_ThreadSafeContextLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ThreadSafeContextUnlock (int /*<<< orphan*/ *) ; 

void *threadMain(void *arg) {
    REDISMODULE_NOT_USED(arg);
    RedisModuleCtx *ctx = RedisModule_GetThreadSafeContext(NULL);
    RedisModule_SelectDb(ctx,9); /* Tests ran in database number 9. */
    for (int i = 0; i < 10; i++) {
        RedisModule_ThreadSafeContextLock(ctx);
        RedisModule_Replicate(ctx,"INCR","c","thread");
        RedisModule_ThreadSafeContextUnlock(ctx);
    }
    RedisModule_FreeThreadSafeContext(ctx);
    return NULL;
}