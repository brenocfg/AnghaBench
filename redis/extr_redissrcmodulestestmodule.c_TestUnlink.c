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
typedef  int /*<<< orphan*/  RedisModuleCallReply ;

/* Variables and functions */
 scalar_t__ REDISMODULE_ERR ; 
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int) ; 
 int REDISMODULE_READ ; 
 int REDISMODULE_WRITE ; 
 int /*<<< orphan*/  RedisModule_AutoMemory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_Call (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int RedisModule_CallReplyInteger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_CreateStringPrintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * RedisModule_OpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int RedisModule_ReplyWithSimpleString (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ RedisModule_StringSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RedisModule_UnlinkKey (int /*<<< orphan*/ *) ; 
 int failTest (int /*<<< orphan*/ *,char*) ; 

int TestUnlink(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx);
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    RedisModuleKey *k = RedisModule_OpenKey(ctx, RedisModule_CreateStringPrintf(ctx, "unlinked"), REDISMODULE_WRITE | REDISMODULE_READ);
    if (!k) return failTest(ctx, "Could not create key");

    if (REDISMODULE_ERR == RedisModule_StringSet(k, RedisModule_CreateStringPrintf(ctx, "Foobar"))) {
        return failTest(ctx, "Could not set string value");
    }

    RedisModuleCallReply *rep = RedisModule_Call(ctx, "EXISTS", "c", "unlinked");
    if (!rep || RedisModule_CallReplyInteger(rep) != 1) {
        return failTest(ctx, "Key does not exist before unlink");
    }

    if (REDISMODULE_ERR == RedisModule_UnlinkKey(k)) {
        return failTest(ctx, "Could not unlink key");
    }

    rep = RedisModule_Call(ctx, "EXISTS", "c", "unlinked");
    if (!rep || RedisModule_CallReplyInteger(rep) != 0) {
        return failTest(ctx, "Could not verify key to be unlinked");
    }
    return RedisModule_ReplyWithSimpleString(ctx, "OK");

}