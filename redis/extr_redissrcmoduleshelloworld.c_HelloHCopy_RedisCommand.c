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
 int /*<<< orphan*/  REDISMODULE_ERRORMSG_WRONGTYPE ; 
 int /*<<< orphan*/  REDISMODULE_HASH_NONE ; 
 int REDISMODULE_KEYTYPE_EMPTY ; 
 int REDISMODULE_KEYTYPE_HASH ; 
 int REDISMODULE_OK ; 
 int REDISMODULE_READ ; 
 int REDISMODULE_WRITE ; 
 int /*<<< orphan*/  RedisModule_AutoMemory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_HashGet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_HashSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RedisModule_KeyType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_OpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int RedisModule_ReplyWithError (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 

int HelloHCopy_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */

    if (argc != 4) return RedisModule_WrongArity(ctx);
    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
    int type = RedisModule_KeyType(key);
    if (type != REDISMODULE_KEYTYPE_HASH &&
        type != REDISMODULE_KEYTYPE_EMPTY)
    {
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    /* Get the old field value. */
    RedisModuleString *oldval;
    RedisModule_HashGet(key,REDISMODULE_HASH_NONE,argv[2],&oldval,NULL);
    if (oldval) {
        RedisModule_HashSet(key,REDISMODULE_HASH_NONE,argv[3],oldval,NULL);
    }
    RedisModule_ReplyWithLongLong(ctx,oldval != NULL);
    return REDISMODULE_OK;
}