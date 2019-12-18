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
 scalar_t__ REDISMODULE_KEYTYPE_EMPTY ; 
 scalar_t__ REDISMODULE_KEYTYPE_LIST ; 
 int /*<<< orphan*/  REDISMODULE_LIST_HEAD ; 
 int /*<<< orphan*/  REDISMODULE_LIST_TAIL ; 
 scalar_t__ REDISMODULE_OK ; 
 int REDISMODULE_READ ; 
 int REDISMODULE_WRITE ; 
 int /*<<< orphan*/  RedisModule_AutoMemory (int /*<<< orphan*/ *) ; 
 scalar_t__ RedisModule_KeyType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_ListPop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_ListPush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_OpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int RedisModule_ReplyWithError (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ RedisModule_StringToLongLong (int /*<<< orphan*/ *,long long*) ; 
 size_t RedisModule_ValueLength (int /*<<< orphan*/ *) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 

int HelloListSpliceAuto_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 4) return RedisModule_WrongArity(ctx);

    RedisModule_AutoMemory(ctx);

    RedisModuleKey *srckey = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
    RedisModuleKey *dstkey = RedisModule_OpenKey(ctx,argv[2],
        REDISMODULE_READ|REDISMODULE_WRITE);

    /* Src and dst key must be empty or lists. */
    if ((RedisModule_KeyType(srckey) != REDISMODULE_KEYTYPE_LIST &&
         RedisModule_KeyType(srckey) != REDISMODULE_KEYTYPE_EMPTY) ||
        (RedisModule_KeyType(dstkey) != REDISMODULE_KEYTYPE_LIST &&
         RedisModule_KeyType(dstkey) != REDISMODULE_KEYTYPE_EMPTY))
    {
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    long long count;
    if ((RedisModule_StringToLongLong(argv[3],&count) != REDISMODULE_OK) ||
        (count < 0))
    {
        return RedisModule_ReplyWithError(ctx,"ERR invalid count");
    }

    while(count-- > 0) {
        RedisModuleString *ele;

        ele = RedisModule_ListPop(srckey,REDISMODULE_LIST_TAIL);
        if (ele == NULL) break;
        RedisModule_ListPush(dstkey,REDISMODULE_LIST_HEAD,ele);
    }

    size_t len = RedisModule_ValueLength(srckey);
    RedisModule_ReplyWithLongLong(ctx,len);
    return REDISMODULE_OK;
}