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
 int /*<<< orphan*/ * RedisModule_Call (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  RedisModule_FreeCallReply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithCallReply (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithError (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* RedisModule_StringPtrLen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_WrongArity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int test_call_generic(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc<2) {
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }

    const char* cmdname = RedisModule_StringPtrLen(argv[1], NULL);
    RedisModuleCallReply *reply = RedisModule_Call(ctx, cmdname, "v", argv+2, argc-2);
    if (reply) {
        RedisModule_ReplyWithCallReply(ctx, reply);
        RedisModule_FreeCallReply(reply);
    } else {
        RedisModule_ReplyWithError(ctx, strerror(errno));
    }
    return REDISMODULE_OK;
}