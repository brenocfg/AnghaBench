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
 int /*<<< orphan*/  FAIL (char*,...) ; 
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int) ; 
 scalar_t__ REDISMODULE_REPLY_NULL ; 
 scalar_t__ REDISMODULE_REPLY_STRING ; 
 int /*<<< orphan*/ * RedisModule_Call (int /*<<< orphan*/ *,char*,char*,...) ; 
 char* RedisModule_CallReplyStringPtr (int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ RedisModule_CallReplyType (int /*<<< orphan*/ *) ; 
 int RedisModule_ReplyWithSimpleString (int /*<<< orphan*/ *,char*) ; 

int TestNotifications(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

#define FAIL(msg, ...)                                                                       \
    {                                                                                        \
        RedisModule_Log(ctx, "warning", "Failed NOTIFY Test. Reason: " #msg, ##__VA_ARGS__); \
        goto err;                                                                            \
    }
    RedisModule_Call(ctx, "FLUSHDB", "");

    RedisModule_Call(ctx, "SET", "cc", "foo", "bar");
    RedisModule_Call(ctx, "SET", "cc", "foo", "baz");
    RedisModule_Call(ctx, "SADD", "cc", "bar", "x");
    RedisModule_Call(ctx, "SADD", "cc", "bar", "y");

    RedisModule_Call(ctx, "HSET", "ccc", "baz", "x", "y");
    /* LPUSH should be ignored and not increment any counters */
    RedisModule_Call(ctx, "LPUSH", "cc", "l", "y");
    RedisModule_Call(ctx, "LPUSH", "cc", "l", "y");

    /* Miss some keys intentionally so we will get a "keymiss" notification. */
    RedisModule_Call(ctx, "GET", "c", "nosuchkey");
    RedisModule_Call(ctx, "SMEMBERS", "c", "nosuchkey");

    size_t sz;
    const char *rep;
    RedisModuleCallReply *r = RedisModule_Call(ctx, "HGET", "cc", "notifications", "foo");
    if (r == NULL || RedisModule_CallReplyType(r) != REDISMODULE_REPLY_STRING) {
        FAIL("Wrong or no reply for foo");
    } else {
        rep = RedisModule_CallReplyStringPtr(r, &sz);
        if (sz != 1 || *rep != '2') {
            FAIL("Got reply '%s'. expected '2'", RedisModule_CallReplyStringPtr(r, NULL));
        }
    }

    r = RedisModule_Call(ctx, "HGET", "cc", "notifications", "bar");
    if (r == NULL || RedisModule_CallReplyType(r) != REDISMODULE_REPLY_STRING) {
        FAIL("Wrong or no reply for bar");
    } else {
        rep = RedisModule_CallReplyStringPtr(r, &sz);
        if (sz != 1 || *rep != '2') {
            FAIL("Got reply '%s'. expected '2'", rep);
        }
    }

    r = RedisModule_Call(ctx, "HGET", "cc", "notifications", "baz");
    if (r == NULL || RedisModule_CallReplyType(r) != REDISMODULE_REPLY_STRING) {
        FAIL("Wrong or no reply for baz");
    } else {
        rep = RedisModule_CallReplyStringPtr(r, &sz);
        if (sz != 1 || *rep != '1') {
            FAIL("Got reply '%.*s'. expected '1'", sz, rep);
        }
    }
    /* For l we expect nothing since we didn't subscribe to list events */
    r = RedisModule_Call(ctx, "HGET", "cc", "notifications", "l");
    if (r == NULL || RedisModule_CallReplyType(r) != REDISMODULE_REPLY_NULL) {
        FAIL("Wrong reply for l");
    }

    r = RedisModule_Call(ctx, "HGET", "cc", "notifications", "nosuchkey");
    if (r == NULL || RedisModule_CallReplyType(r) != REDISMODULE_REPLY_STRING) {
        FAIL("Wrong or no reply for nosuchkey");
    } else {
        rep = RedisModule_CallReplyStringPtr(r, &sz);
        if (sz != 1 || *rep != '2') {
            FAIL("Got reply '%.*s'. expected '2'", sz, rep);
        }
    }

    RedisModule_Call(ctx, "FLUSHDB", "");

    return RedisModule_ReplyWithSimpleString(ctx, "OK");
err:
    RedisModule_Call(ctx, "FLUSHDB", "");

    return RedisModule_ReplyWithSimpleString(ctx, "ERR");
}