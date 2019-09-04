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
typedef  int /*<<< orphan*/  RedisModuleCallReply ;

/* Variables and functions */
 int REDISMODULE_OK ; 
 int /*<<< orphan*/ * RedisModule_Call (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,long long,long long) ; 
 int /*<<< orphan*/ * RedisModule_CallReplyArrayElement (int /*<<< orphan*/ *,size_t) ; 
 size_t RedisModule_CallReplyLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_FreeCallReply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,size_t) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 

int HelloListSumLen_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc != 2) return RedisModule_WrongArity(ctx);

    RedisModuleCallReply *reply;

    reply = RedisModule_Call(ctx,"LRANGE","sll",argv[1],(long long)0,(long long)-1);
    size_t strlen = 0;
    size_t items = RedisModule_CallReplyLength(reply);
    size_t j;
    for (j = 0; j < items; j++) {
        RedisModuleCallReply *ele = RedisModule_CallReplyArrayElement(reply,j);
        strlen += RedisModule_CallReplyLength(ele);
    }
    RedisModule_FreeCallReply(reply);
    RedisModule_ReplyWithLongLong(ctx,strlen);
    return REDISMODULE_OK;
}