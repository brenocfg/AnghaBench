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
 int /*<<< orphan*/ * RedisModule_Call (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  RedisModule_FreeCallReply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithCallReply (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithError (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int test_call_info(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    RedisModuleCallReply *reply;
    if (argc>1)
        reply = RedisModule_Call(ctx, "info", "s", argv[1]);
    else
        reply = RedisModule_Call(ctx, "info", "");
    if (reply) {
        RedisModule_ReplyWithCallReply(ctx, reply);
        RedisModule_FreeCallReply(reply);
    } else {
        RedisModule_ReplyWithError(ctx, strerror(errno));
    }
    return REDISMODULE_OK;
}