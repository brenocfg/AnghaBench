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
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int) ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  RedisModule_AutoMemory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_Call (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  RedisModule_Replicate (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int HelloRepl1_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);
    RedisModule_AutoMemory(ctx);

    /* This will be replicated *after* the two INCR statements, since
     * the Call() replication has precedence, so the actual replication
     * stream will be:
     *
     * MULTI
     * INCR foo
     * INCR bar
     * ECHO c foo
     * EXEC
     */
    RedisModule_Replicate(ctx,"ECHO","c","foo");

    /* Using the "!" modifier we replicate the command if it
     * modified the dataset in some way. */
    RedisModule_Call(ctx,"INCR","c!","foo");
    RedisModule_Call(ctx,"INCR","c!","bar");

    RedisModule_ReplyWithLongLong(ctx,0);

    return REDISMODULE_OK;
}