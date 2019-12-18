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
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  RedisModule_ExitFromChild (long long) ; 
 scalar_t__ RedisModule_Fork (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  RedisModule_Log (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithError (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  RedisModule_StringToLongLong (int /*<<< orphan*/ *,long long*) ; 
 int /*<<< orphan*/  RedisModule_WrongArity (int /*<<< orphan*/ *) ; 
 scalar_t__ child_pid ; 
 int /*<<< orphan*/  done_handler ; 
 int exitted_with_code ; 
 int /*<<< orphan*/  usleep (int) ; 

int fork_create(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    long long code_to_exit_with;
    if (argc != 2) {
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }
    RedisModule_StringToLongLong(argv[1], &code_to_exit_with);
    exitted_with_code = -1;
    child_pid = RedisModule_Fork(done_handler, (void*)0xdeadbeef);
    if (child_pid < 0) {
        RedisModule_ReplyWithError(ctx, "Fork failed");
        return REDISMODULE_OK;
    } else if (child_pid > 0) {
        /* parent */
        RedisModule_ReplyWithLongLong(ctx, child_pid);
        return REDISMODULE_OK;
    }

    /* child */
    RedisModule_Log(ctx, "notice", "fork child started");
    usleep(200000);
    RedisModule_Log(ctx, "notice", "fork child exiting");
    RedisModule_ExitFromChild(code_to_exit_with);
    /* unreachable */
    return 0;
}