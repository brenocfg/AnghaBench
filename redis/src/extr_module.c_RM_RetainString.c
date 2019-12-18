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
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_AM_STRING ; 
 int /*<<< orphan*/  autoMemoryFreed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  incrRefCount (int /*<<< orphan*/ *) ; 

void RM_RetainString(RedisModuleCtx *ctx, RedisModuleString *str) {
    if (ctx == NULL || !autoMemoryFreed(ctx,REDISMODULE_AM_STRING,str)) {
        /* Increment the string reference counting only if we can't
         * just remove the object from the list of objects that should
         * be reclaimed. Why we do that, instead of just incrementing
         * the refcount in any case, and let the automatic FreeString()
         * call at the end to bring the refcount back at the desired
         * value? Because this way we ensure that the object refcount
         * value is 1 (instead of going to 2 to be dropped later to 1)
         * after the call to this function. This is needed for functions
         * like RedisModule_StringAppendBuffer() to work. */
        incrRefCount(str);
    }
}