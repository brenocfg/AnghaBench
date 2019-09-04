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
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int) ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  RedisModule_AutoMemory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_Call (int /*<<< orphan*/ *,char*,char*,char*,...) ; 
 int /*<<< orphan*/ * RedisModule_CallReplyArrayElement (int /*<<< orphan*/ *,int) ; 
 long long RedisModule_CallReplyLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_CreateString (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithSimpleString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TestMatchReply (int /*<<< orphan*/ *,char*) ; 

int TestCall(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    RedisModule_AutoMemory(ctx);
    RedisModuleCallReply *reply;

    RedisModule_Call(ctx,"DEL","c","mylist");
    RedisModuleString *mystr = RedisModule_CreateString(ctx,"foo",3);
    RedisModule_Call(ctx,"RPUSH","csl","mylist",mystr,(long long)1234);
    reply = RedisModule_Call(ctx,"LRANGE","ccc","mylist","0","-1");
    long long items = RedisModule_CallReplyLength(reply);
    if (items != 2) goto fail;

    RedisModuleCallReply *item0, *item1;

    item0 = RedisModule_CallReplyArrayElement(reply,0);
    item1 = RedisModule_CallReplyArrayElement(reply,1);
    if (!TestMatchReply(item0,"foo")) goto fail;
    if (!TestMatchReply(item1,"1234")) goto fail;

    RedisModule_ReplyWithSimpleString(ctx,"OK");
    return REDISMODULE_OK;

fail:
    RedisModule_ReplyWithSimpleString(ctx,"ERR");
    return REDISMODULE_OK;
}