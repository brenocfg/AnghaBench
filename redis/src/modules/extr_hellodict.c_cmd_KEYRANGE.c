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
typedef  int /*<<< orphan*/  RedisModuleDictIter ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  Keyspace ; 
 scalar_t__ REDISMODULE_ERR ; 
 scalar_t__ REDISMODULE_OK ; 
 int /*<<< orphan*/  REDISMODULE_POSTPONED_ARRAY_LEN ; 
 scalar_t__ RedisModule_DictCompare (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_DictIteratorStart (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_DictIteratorStop (int /*<<< orphan*/ *) ; 
 char* RedisModule_DictNextC (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ReplySetArrayLength (int /*<<< orphan*/ *,long long) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithArray (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RedisModule_ReplyWithError (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithStringBuffer (int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ RedisModule_StringToLongLong (int /*<<< orphan*/ *,long long*) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 

int cmd_KEYRANGE(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 4) return RedisModule_WrongArity(ctx);

    /* Parse the count argument. */
    long long count;
    if (RedisModule_StringToLongLong(argv[3],&count) != REDISMODULE_OK) {
        return RedisModule_ReplyWithError(ctx,"ERR invalid count");
    }

    /* Seek the iterator. */
    RedisModuleDictIter *iter = RedisModule_DictIteratorStart(
        Keyspace, ">=", argv[1]);

    /* Reply with the matching items. */
    char *key;
    size_t keylen;
    long long replylen = 0; /* Keep track of the amitted array len. */
    RedisModule_ReplyWithArray(ctx,REDISMODULE_POSTPONED_ARRAY_LEN);
    while((key = RedisModule_DictNextC(iter,&keylen,NULL)) != NULL) {
        if (replylen >= count) break;
        if (RedisModule_DictCompare(iter,"<=",argv[2]) == REDISMODULE_ERR)
            break;
        RedisModule_ReplyWithStringBuffer(ctx,key,keylen);
        replylen++;
    }
    RedisModule_ReplySetArrayLength(ctx,replylen);

    /* Cleanup. */
    RedisModule_DictIteratorStop(iter);
    return REDISMODULE_OK;
}