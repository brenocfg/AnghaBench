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
typedef  scalar_t__ mstime_t ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleKey ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 scalar_t__ REDISMODULE_NO_EXPIRE ; 
 scalar_t__ REDISMODULE_OK ; 
 int REDISMODULE_READ ; 
 int REDISMODULE_WRITE ; 
 int /*<<< orphan*/  RedisModule_AutoMemory (int /*<<< orphan*/ *) ; 
 scalar_t__ RedisModule_GetExpire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_OpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int RedisModule_ReplyWithError (int /*<<< orphan*/ *,char*) ; 
 int RedisModule_ReplyWithSimpleString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RedisModule_SetExpire (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ RedisModule_StringToLongLong (int /*<<< orphan*/ *,scalar_t__*) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 

int HelloMoreExpire_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */
    if (argc != 3) return RedisModule_WrongArity(ctx);

    mstime_t addms, expire;

    if (RedisModule_StringToLongLong(argv[2],&addms) != REDISMODULE_OK)
        return RedisModule_ReplyWithError(ctx,"ERR invalid expire time");

    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
    expire = RedisModule_GetExpire(key);
    if (expire != REDISMODULE_NO_EXPIRE) {
        expire += addms;
        RedisModule_SetExpire(key,expire);
    }
    return RedisModule_ReplyWithSimpleString(ctx,"OK");
}