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
 scalar_t__ REDISMODULE_OK ; 
 int /*<<< orphan*/  RedisModule_ReplyWithArray (int /*<<< orphan*/ *,long long) ; 
 int RedisModule_ReplyWithError (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RedisModule_StringToLongLong (int /*<<< orphan*/ *,long long*) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rand () ; 

int HelloRandArray_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 2) return RedisModule_WrongArity(ctx);
    long long count;
    if (RedisModule_StringToLongLong(argv[1],&count) != REDISMODULE_OK ||
        count < 0)
        return RedisModule_ReplyWithError(ctx,"ERR invalid count");

    /* To reply with an array, we call RedisModule_ReplyWithArray() followed
     * by other "count" calls to other reply functions in order to generate
     * the elements of the array. */
    RedisModule_ReplyWithArray(ctx,count);
    while(count--) RedisModule_ReplyWithLongLong(ctx,rand());
    return REDISMODULE_OK;
}