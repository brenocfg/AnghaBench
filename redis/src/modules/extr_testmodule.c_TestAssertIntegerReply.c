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
typedef  int /*<<< orphan*/  RedisModuleCtx ;
typedef  int /*<<< orphan*/  RedisModuleCallReply ;

/* Variables and functions */
 scalar_t__ REDISMODULE_REPLY_INTEGER ; 
 long long RedisModule_CallReplyInteger (int /*<<< orphan*/ *) ; 
 scalar_t__ RedisModule_CallReplyType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_Log (int /*<<< orphan*/ *,char*,char*,long long,...) ; 

int TestAssertIntegerReply(RedisModuleCtx *ctx, RedisModuleCallReply *reply, long long expected) {
    if (RedisModule_CallReplyType(reply) != REDISMODULE_REPLY_INTEGER) {
        RedisModule_Log(ctx,"warning","Unexpected reply type %d",
            RedisModule_CallReplyType(reply));
        return 0;
    }
    long long val = RedisModule_CallReplyInteger(reply);
    if (val != expected) {
        RedisModule_Log(ctx,"warning",
            "Unexpected integer reply '%lld' (instead of '%lld')",
            val, expected);
        return 0;
    }
    return 1;
}