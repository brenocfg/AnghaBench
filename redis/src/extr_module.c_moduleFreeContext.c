#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; int /*<<< orphan*/  client; TYPE_1__* module; scalar_t__ postponed_arrays_count; scalar_t__ postponed_arrays; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 int REDISMODULE_CTX_THREAD_SAFE ; 
 int /*<<< orphan*/  autoMemoryCollect (TYPE_2__*) ; 
 int /*<<< orphan*/  freeClient (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moduleHandlePropagationAfterCommandCallback (TYPE_2__*) ; 
 int /*<<< orphan*/  poolAllocRelease (TYPE_2__*) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (scalar_t__) ; 

void moduleFreeContext(RedisModuleCtx *ctx) {
    moduleHandlePropagationAfterCommandCallback(ctx);
    autoMemoryCollect(ctx);
    poolAllocRelease(ctx);
    if (ctx->postponed_arrays) {
        zfree(ctx->postponed_arrays);
        ctx->postponed_arrays_count = 0;
        serverLog(LL_WARNING,
            "API misuse detected in module %s: "
            "RedisModule_ReplyWithArray(REDISMODULE_POSTPONED_ARRAY_LEN) "
            "not matched by the same number of RedisModule_SetReplyArrayLen() "
            "calls.",
            ctx->module->name);
    }
    if (ctx->flags & REDISMODULE_CTX_THREAD_SAFE) freeClient(ctx->client);
}