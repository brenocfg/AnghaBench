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
 int /*<<< orphan*/  RedisModule_CreateTimer (void*,int,void (*) (void*,void*),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_Replicate (void*,char*,char*,char*) ; 

void timerHandler(RedisModuleCtx *ctx, void *data) {
    REDISMODULE_NOT_USED(ctx);
    REDISMODULE_NOT_USED(data);

    static int times = 0;

    RedisModule_Replicate(ctx,"INCR","c","timer");
    times++;

    if (times < 10)
        RedisModule_CreateTimer(ctx,100,timerHandler,NULL);
    else
        times = 0;
}