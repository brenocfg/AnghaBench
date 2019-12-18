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
 int /*<<< orphan*/  HelloBlock_FreeData ; 
 int /*<<< orphan*/  HelloBlock_Reply ; 
 int /*<<< orphan*/  HelloBlock_Timeout ; 
 scalar_t__ HelloType ; 
 int HelloTypeRange_RedisCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 char* REDISMODULE_ERRORMSG_WRONGTYPE ; 
 int REDISMODULE_KEYTYPE_EMPTY ; 
 scalar_t__ REDISMODULE_OK ; 
 int REDISMODULE_READ ; 
 int REDISMODULE_WRITE ; 
 void* RedisModule_Alloc (int) ; 
 int /*<<< orphan*/  RedisModule_AutoMemory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_BlockClientOnKeys (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long long,int /*<<< orphan*/ **,int,void*) ; 
 int RedisModule_KeyType (int /*<<< orphan*/ *) ; 
 scalar_t__ RedisModule_ModuleTypeGetType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_OpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int RedisModule_ReplyWithError (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ RedisModule_StringToLongLong (int /*<<< orphan*/ *,long long*) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 

int HelloTypeBRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 5) return RedisModule_WrongArity(ctx);
    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */
    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
    int type = RedisModule_KeyType(key);
    if (type != REDISMODULE_KEYTYPE_EMPTY &&
        RedisModule_ModuleTypeGetType(key) != HelloType)
    {
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    /* Parse the timeout before even trying to serve the client synchronously,
     * so that we always fail ASAP on syntax errors. */
    long long timeout;
    if (RedisModule_StringToLongLong(argv[4],&timeout) != REDISMODULE_OK) {
        return RedisModule_ReplyWithError(ctx,
            "ERR invalid timeout parameter");
    }

    /* Can we serve the reply synchronously? */
    if (type != REDISMODULE_KEYTYPE_EMPTY) {
        return HelloTypeRange_RedisCommand(ctx,argv,argc-1);
    }

    /* Otherwise let's block on the key. */
    void *privdata = RedisModule_Alloc(100);
    RedisModule_BlockClientOnKeys(ctx,HelloBlock_Reply,HelloBlock_Timeout,HelloBlock_FreeData,timeout,argv+1,1,privdata);
    return REDISMODULE_OK;
}