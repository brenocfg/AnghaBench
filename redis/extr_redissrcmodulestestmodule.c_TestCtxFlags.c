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

/* Variables and functions */
 int REDISMODULE_CTX_FLAGS_AOF ; 
 int REDISMODULE_CTX_FLAGS_CLUSTER ; 
 int REDISMODULE_CTX_FLAGS_EVICT ; 
 int REDISMODULE_CTX_FLAGS_LUA ; 
 int REDISMODULE_CTX_FLAGS_MASTER ; 
 int REDISMODULE_CTX_FLAGS_MAXMEMORY ; 
 int REDISMODULE_CTX_FLAGS_MULTI ; 
 int REDISMODULE_CTX_FLAGS_RDB ; 
 int REDISMODULE_CTX_FLAGS_READONLY ; 
 int REDISMODULE_CTX_FLAGS_SLAVE ; 
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int) ; 
 int /*<<< orphan*/  RedisModule_AutoMemory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_Call (int /*<<< orphan*/ *,char*,char*,char*,char*,char*) ; 
 int RedisModule_GetContextFlags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_Log (int /*<<< orphan*/ *,char*,char*,char const*) ; 
 int RedisModule_ReplyWithSimpleString (int /*<<< orphan*/ *,char*) ; 

int TestCtxFlags(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argc);
    REDISMODULE_NOT_USED(argv);

    RedisModule_AutoMemory(ctx);

    int ok = 1;
    const char *errString = NULL;
#undef FAIL
#define FAIL(msg)        \
    {                    \
        ok = 0;          \
        errString = msg; \
        goto end;        \
    }

    int flags = RedisModule_GetContextFlags(ctx);
    if (flags == 0) {
        FAIL("Got no flags");
    }

    if (flags & REDISMODULE_CTX_FLAGS_LUA) FAIL("Lua flag was set");
    if (flags & REDISMODULE_CTX_FLAGS_MULTI) FAIL("Multi flag was set");

    if (flags & REDISMODULE_CTX_FLAGS_AOF) FAIL("AOF Flag was set")
    /* Enable AOF to test AOF flags */
    RedisModule_Call(ctx, "config", "ccc", "set", "appendonly", "yes");
    flags = RedisModule_GetContextFlags(ctx);
    if (!(flags & REDISMODULE_CTX_FLAGS_AOF)) FAIL("AOF Flag not set after config set");

    if (flags & REDISMODULE_CTX_FLAGS_RDB) FAIL("RDB Flag was set");
    /* Enable RDB to test RDB flags */
    RedisModule_Call(ctx, "config", "ccc", "set", "save", "900 1");
    flags = RedisModule_GetContextFlags(ctx);
    if (!(flags & REDISMODULE_CTX_FLAGS_RDB)) FAIL("RDB Flag was not set after config set");

    if (!(flags & REDISMODULE_CTX_FLAGS_MASTER)) FAIL("Master flag was not set");
    if (flags & REDISMODULE_CTX_FLAGS_SLAVE) FAIL("Slave flag was set");
    if (flags & REDISMODULE_CTX_FLAGS_READONLY) FAIL("Read-only flag was set");
    if (flags & REDISMODULE_CTX_FLAGS_CLUSTER) FAIL("Cluster flag was set");

    if (flags & REDISMODULE_CTX_FLAGS_MAXMEMORY) FAIL("Maxmemory flag was set");

    RedisModule_Call(ctx, "config", "ccc", "set", "maxmemory", "100000000");
    flags = RedisModule_GetContextFlags(ctx);
    if (!(flags & REDISMODULE_CTX_FLAGS_MAXMEMORY))
        FAIL("Maxmemory flag was not set after config set");

    if (flags & REDISMODULE_CTX_FLAGS_EVICT) FAIL("Eviction flag was set");
    RedisModule_Call(ctx, "config", "ccc", "set", "maxmemory-policy", "allkeys-lru");
    flags = RedisModule_GetContextFlags(ctx);
    if (!(flags & REDISMODULE_CTX_FLAGS_EVICT)) FAIL("Eviction flag was not set after config set");

end:
    /* Revert config changes */
    RedisModule_Call(ctx, "config", "ccc", "set", "appendonly", "no");
    RedisModule_Call(ctx, "config", "ccc", "set", "save", "");
    RedisModule_Call(ctx, "config", "ccc", "set", "maxmemory", "0");
    RedisModule_Call(ctx, "config", "ccc", "set", "maxmemory-policy", "noeviction");

    if (!ok) {
        RedisModule_Log(ctx, "warning", "Failed CTXFLAGS Test. Reason: %s", errString);
        return RedisModule_ReplyWithSimpleString(ctx, "ERR");
    }

    return RedisModule_ReplyWithSimpleString(ctx, "OK");
}