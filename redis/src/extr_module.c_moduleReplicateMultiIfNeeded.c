#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  also_propagate; } ;
struct TYPE_5__ {int flags; TYPE_4__* client; int /*<<< orphan*/  saved_oparray; } ;
typedef  TYPE_1__ RedisModuleCtx ;

/* Variables and functions */
 int CLIENT_LUA ; 
 int CLIENT_MULTI ; 
 int REDISMODULE_CTX_MODULE_COMMAND_CALL ; 
 int REDISMODULE_CTX_MULTI_EMITTED ; 
 int REDISMODULE_CTX_THREAD_SAFE ; 
 int /*<<< orphan*/  execCommandPropagateMulti (TYPE_4__*) ; 
 int /*<<< orphan*/  redisOpArrayInit (int /*<<< orphan*/ *) ; 
 TYPE_2__ server ; 

void moduleReplicateMultiIfNeeded(RedisModuleCtx *ctx) {
    /* Skip this if client explicitly wrap the command with MULTI, or if
     * the module command was called by a script. */
    if (ctx->client->flags & (CLIENT_MULTI|CLIENT_LUA)) return;
    /* If we already emitted MULTI return ASAP. */
    if (ctx->flags & REDISMODULE_CTX_MULTI_EMITTED) return;
    /* If this is a thread safe context, we do not want to wrap commands
     * executed into MULTI/EXEC, they are executed as single commands
     * from an external client in essence. */
    if (ctx->flags & REDISMODULE_CTX_THREAD_SAFE) return;
    /* If this is a callback context, and not a module command execution
     * context, we have to setup the op array for the "also propagate" API
     * so that RM_Replicate() will work. */
    if (!(ctx->flags & REDISMODULE_CTX_MODULE_COMMAND_CALL)) {
        ctx->saved_oparray = server.also_propagate;
        redisOpArrayInit(&server.also_propagate);
    }
    execCommandPropagateMulti(ctx->client);
    ctx->flags |= REDISMODULE_CTX_MULTI_EMITTED;
}