#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int argc; TYPE_5__** argv; TYPE_1__* cmd; } ;
typedef  TYPE_2__ client ;
struct TYPE_14__ {int refcount; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* func ) (TYPE_3__*,void**,int) ;int /*<<< orphan*/  module; } ;
struct TYPE_12__ {TYPE_2__* client; int /*<<< orphan*/  module; int /*<<< orphan*/  flags; } ;
struct TYPE_10__ {scalar_t__ getkeys_proc; } ;
typedef  TYPE_3__ RedisModuleCtx ;
typedef  TYPE_4__ RedisModuleCommandProxy ;

/* Variables and functions */
 TYPE_3__ REDISMODULE_CTX_INIT ; 
 int /*<<< orphan*/  REDISMODULE_CTX_MODULE_COMMAND_CALL ; 
 int /*<<< orphan*/  moduleFreeContext (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,void**,int) ; 
 int /*<<< orphan*/  trimStringObjectIfNeeded (TYPE_5__*) ; 

void RedisModuleCommandDispatcher(client *c) {
    RedisModuleCommandProxy *cp = (void*)(unsigned long)c->cmd->getkeys_proc;
    RedisModuleCtx ctx = REDISMODULE_CTX_INIT;

    ctx.flags |= REDISMODULE_CTX_MODULE_COMMAND_CALL;
    ctx.module = cp->module;
    ctx.client = c;
    cp->func(&ctx,(void**)c->argv,c->argc);
    moduleFreeContext(&ctx);

    /* In some cases processMultibulkBuffer uses sdsMakeRoomFor to
     * expand the query buffer, and in order to avoid a big object copy
     * the query buffer SDS may be used directly as the SDS string backing
     * the client argument vectors: sometimes this will result in the SDS
     * string having unused space at the end. Later if a module takes ownership
     * of the RedisString, such space will be wasted forever. Inside the
     * Redis core this is not a problem because tryObjectEncoding() is called
     * before storing strings in the key space. Here we need to do it
     * for the module. */
    for (int i = 0; i < c->argc; i++) {
        /* Only do the work if the module took ownership of the object:
         * in that case the refcount is no longer 1. */
        if (c->argv[i]->refcount > 1)
            trimStringObjectIfNeeded(c->argv[i]);
    }
}