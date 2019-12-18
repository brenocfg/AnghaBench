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
 scalar_t__ REDISMODULE_KEYTYPE_LIST ; 
 int /*<<< orphan*/  REDISMODULE_LIST_HEAD ; 
 int /*<<< orphan*/  REDISMODULE_LIST_TAIL ; 
 scalar_t__ REDISMODULE_OK ; 
 int REDISMODULE_READ ; 
 int REDISMODULE_WRITE ; 
 int /*<<< orphan*/  RedisModule_AutoMemory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_CreateStringFromLongLong (int /*<<< orphan*/ *,long long) ; 
 scalar_t__ RedisModule_KeyType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_ListPop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_ListPush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_OpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RedisModule_ReplicateVerbatim (int /*<<< orphan*/ *) ; 
 int RedisModule_ReplyWithError (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,long long) ; 
 scalar_t__ RedisModule_StringToLongLong (int /*<<< orphan*/ *,long long*) ; 
 size_t RedisModule_ValueLength (int /*<<< orphan*/ *) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 

int HelloRepl2_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 2) return RedisModule_WrongArity(ctx);

    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */
    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);

    if (RedisModule_KeyType(key) != REDISMODULE_KEYTYPE_LIST)
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);

    size_t listlen = RedisModule_ValueLength(key);
    long long sum = 0;

    /* Rotate and increment. */
    while(listlen--) {
        RedisModuleString *ele = RedisModule_ListPop(key,REDISMODULE_LIST_TAIL);
        long long val;
        if (RedisModule_StringToLongLong(ele,&val) != REDISMODULE_OK) val = 0;
        val++;
        sum += val;
        RedisModuleString *newele = RedisModule_CreateStringFromLongLong(ctx,val);
        RedisModule_ListPush(key,REDISMODULE_LIST_HEAD,newele);
    }
    RedisModule_ReplyWithLongLong(ctx,sum);
    RedisModule_ReplicateVerbatim(ctx);
    return REDISMODULE_OK;
}