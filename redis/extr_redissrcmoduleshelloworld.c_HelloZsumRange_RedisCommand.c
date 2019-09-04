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
 int REDISMODULE_READ ; 
 int REDISMODULE_WRITE ; 
 int /*<<< orphan*/  RedisModule_CloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_FreeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RedisModule_KeyType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_OpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithArray (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithDouble (int /*<<< orphan*/ *,double) ; 
 int RedisModule_ReplyWithError (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ RedisModule_StringToDouble (int /*<<< orphan*/ *,double*) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ZsetFirstInScoreRange (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_ZsetLastInScoreRange (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RedisModule_ZsetRangeCurrentElement (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  RedisModule_ZsetRangeEndReached (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ZsetRangeNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ZsetRangePrev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ZsetRangeStop (int /*<<< orphan*/ *) ; 

int HelloZsumRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    double score_start, score_end;
    if (argc != 4) return RedisModule_WrongArity(ctx);

    if (RedisModule_StringToDouble(argv[2],&score_start) != REDISMODULE_OK ||
        RedisModule_StringToDouble(argv[3],&score_end) != REDISMODULE_OK)
    {
        return RedisModule_ReplyWithError(ctx,"ERR invalid range");
    }

    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
    if (RedisModule_KeyType(key) != REDISMODULE_KEYTYPE_ZSET) {
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    double scoresum_a = 0;
    double scoresum_b = 0;

    RedisModule_ZsetFirstInScoreRange(key,score_start,score_end,0,0);
    while(!RedisModule_ZsetRangeEndReached(key)) {
        double score;
        RedisModuleString *ele = RedisModule_ZsetRangeCurrentElement(key,&score);
        RedisModule_FreeString(ctx,ele);
        scoresum_a += score;
        RedisModule_ZsetRangeNext(key);
    }
    RedisModule_ZsetRangeStop(key);

    RedisModule_ZsetLastInScoreRange(key,score_start,score_end,0,0);
    while(!RedisModule_ZsetRangeEndReached(key)) {
        double score;
        RedisModuleString *ele = RedisModule_ZsetRangeCurrentElement(key,&score);
        RedisModule_FreeString(ctx,ele);
        scoresum_b += score;
        RedisModule_ZsetRangePrev(key);
    }

    RedisModule_ZsetRangeStop(key);

    RedisModule_CloseKey(key);

    RedisModule_ReplyWithArray(ctx,2);
    RedisModule_ReplyWithDouble(ctx,scoresum_a);
    RedisModule_ReplyWithDouble(ctx,scoresum_b);
    return REDISMODULE_OK;
}