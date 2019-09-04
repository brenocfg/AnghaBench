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
 int /*<<< orphan*/  RedisModule_ReplyWithSimpleString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  T (char*,char*,...) ; 
 int /*<<< orphan*/  TestAssertIntegerReply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TestAssertStringReply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 

int TestIt(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    RedisModule_AutoMemory(ctx);
    RedisModuleCallReply *reply;

    /* Make sure the DB is empty before to proceed. */
    T("dbsize","");
    if (!TestAssertIntegerReply(ctx,reply,0)) goto fail;

    T("ping","");
    if (!TestAssertStringReply(ctx,reply,"PONG",4)) goto fail;

    T("test.call","");
    if (!TestAssertStringReply(ctx,reply,"OK",2)) goto fail;

    T("test.ctxflags","");
    if (!TestAssertStringReply(ctx,reply,"OK",2)) goto fail;

    T("test.string.append","");
    if (!TestAssertStringReply(ctx,reply,"foobar",6)) goto fail;

    T("test.unlink","");
    if (!TestAssertStringReply(ctx,reply,"OK",2)) goto fail;

    T("test.string.append.am","");
    if (!TestAssertStringReply(ctx,reply,"foobar",6)) goto fail;

    T("test.string.printf", "cc", "foo", "bar");
    if (!TestAssertStringReply(ctx,reply,"Got 3 args. argv[1]: foo, argv[2]: bar",38)) goto fail;

    T("test.notify", "");
    if (!TestAssertStringReply(ctx,reply,"OK",2)) goto fail;

    RedisModule_ReplyWithSimpleString(ctx,"ALL TESTS PASSED");
    return REDISMODULE_OK;

fail:
    RedisModule_ReplyWithSimpleString(ctx,
        "SOME TEST NOT PASSED! Check server logs");
    return REDISMODULE_OK;
}