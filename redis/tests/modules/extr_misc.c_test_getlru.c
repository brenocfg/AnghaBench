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
typedef  int /*<<< orphan*/  RedisModuleKey ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int REDISMODULE_OK ; 
 int REDISMODULE_OPEN_KEY_NOTOUCH ; 
 int REDISMODULE_READ ; 
 int /*<<< orphan*/  RedisModule_CloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_GetLRUOrLFU (int /*<<< orphan*/ *,long long*,long long*) ; 
 int /*<<< orphan*/ * RedisModule_OpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,long long) ; 
 int /*<<< orphan*/  RedisModule_WrongArity (int /*<<< orphan*/ *) ; 

int test_getlru(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc<2) {
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }
    RedisModuleString *keyname = argv[1];
    RedisModuleKey *key = RedisModule_OpenKey(ctx, keyname, REDISMODULE_READ|REDISMODULE_OPEN_KEY_NOTOUCH);
    long long lru, lfu;
    RedisModule_GetLRUOrLFU(key, &lfu, &lru);
    RedisModule_ReplyWithLongLong(ctx, lru);
    RedisModule_CloseKey(key);
    return REDISMODULE_OK;
}