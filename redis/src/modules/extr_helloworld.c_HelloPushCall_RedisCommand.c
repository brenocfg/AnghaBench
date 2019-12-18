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
 int /*<<< orphan*/ * RedisModule_Call (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 long long RedisModule_CallReplyInteger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_FreeCallReply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,long long) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 

int HelloPushCall_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc != 3) return RedisModule_WrongArity(ctx);

    RedisModuleCallReply *reply;

    reply = RedisModule_Call(ctx,"RPUSH","ss",argv[1],argv[2]);
    long long len = RedisModule_CallReplyInteger(reply);
    RedisModule_FreeCallReply(reply);
    RedisModule_ReplyWithLongLong(ctx,len);
    return REDISMODULE_OK;
}