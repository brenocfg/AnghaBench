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
 int /*<<< orphan*/  RedisModule_FreeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_RandomKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int test_randomkey(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);
    RedisModuleString *str = RedisModule_RandomKey(ctx);
    RedisModule_ReplyWithString(ctx, str);
    RedisModule_FreeString(ctx, str);
    return REDISMODULE_OK;
}