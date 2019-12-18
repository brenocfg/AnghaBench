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
 char* REDISMODULE_ERRORMSG_WRONGTYPE ; 
 scalar_t__ REDISMODULE_KEYTYPE_ZSET ; 
 scalar_t__ REDISMODULE_OK ; 
 int /*<<< orphan*/  REDISMODULE_POSTPONED_ARRAY_LEN ; 
 int REDISMODULE_READ ; 
 int REDISMODULE_WRITE ; 
 int /*<<< orphan*/  RedisModule_AutoMemory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_CloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_FreeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RedisModule_KeyType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_OpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RedisModule_ReplySetArrayLength (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithArray (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RedisModule_ReplyWithError (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 
 scalar_t__ RedisModule_ZsetFirstInLexRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_ZsetRangeCurrentElement (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  RedisModule_ZsetRangeEndReached (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ZsetRangeNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ZsetRangeStop (int /*<<< orphan*/ *) ; 

int HelloLexRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */

    if (argc != 6) return RedisModule_WrongArity(ctx);

    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
    if (RedisModule_KeyType(key) != REDISMODULE_KEYTYPE_ZSET) {
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    if (RedisModule_ZsetFirstInLexRange(key,argv[2],argv[3]) != REDISMODULE_OK) {
        return RedisModule_ReplyWithError(ctx,"invalid range");
    }

    int arraylen = 0;
    RedisModule_ReplyWithArray(ctx,REDISMODULE_POSTPONED_ARRAY_LEN);
    while(!RedisModule_ZsetRangeEndReached(key)) {
        double score;
        RedisModuleString *ele = RedisModule_ZsetRangeCurrentElement(key,&score);
        RedisModule_ReplyWithString(ctx,ele);
        RedisModule_FreeString(ctx,ele);
        RedisModule_ZsetRangeNext(key);
        arraylen++;
    }
    RedisModule_ZsetRangeStop(key);
    RedisModule_ReplySetArrayLength(ctx,arraylen);
    RedisModule_CloseKey(key);
    return REDISMODULE_OK;
}