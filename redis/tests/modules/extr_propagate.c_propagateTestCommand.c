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
typedef  int pthread_t ;
typedef  int RedisModuleTimerID ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int) ; 
 int REDISMODULE_OK ; 
 int RedisModule_CreateTimer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int RedisModule_ReplyWithError (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithSimpleString (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ pthread_create (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  threadMain ; 
 int /*<<< orphan*/  timerHandler ; 

int propagateTestCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    RedisModuleTimerID timer_id =
        RedisModule_CreateTimer(ctx,100,timerHandler,NULL);
    REDISMODULE_NOT_USED(timer_id);

    pthread_t tid;
    if (pthread_create(&tid,NULL,threadMain,NULL) != 0)
        return RedisModule_ReplyWithError(ctx,"-ERR Can't start thread");
    REDISMODULE_NOT_USED(tid);

    RedisModule_ReplyWithSimpleString(ctx,"OK");
    return REDISMODULE_OK;
}