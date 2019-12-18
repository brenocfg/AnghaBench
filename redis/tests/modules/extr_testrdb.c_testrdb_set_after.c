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
 int /*<<< orphan*/  RedisModule_FreeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RedisModule_RetainString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_WrongArity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * after_str ; 

int testrdb_set_after(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc != 2){
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }

    if (after_str)
        RedisModule_FreeString(ctx, after_str);
    after_str = argv[1];
    RedisModule_RetainString(ctx, argv[1]);
    RedisModule_ReplyWithLongLong(ctx, 1);
    return REDISMODULE_OK;
}