#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* module_blocked_handle; } ;
struct TYPE_12__ {TYPE_1__ bpop; } ;
typedef  TYPE_2__ client ;
struct TYPE_14__ {int /*<<< orphan*/ * client; int /*<<< orphan*/  (* disconnect_callback ) (TYPE_3__*,TYPE_4__*) ;int /*<<< orphan*/  module; int /*<<< orphan*/  privdata; } ;
struct TYPE_13__ {int /*<<< orphan*/ * client; int /*<<< orphan*/  module; int /*<<< orphan*/  blocked_privdata; } ;
typedef  TYPE_3__ RedisModuleCtx ;
typedef  TYPE_4__ RedisModuleBlockedClient ;

/* Variables and functions */
 TYPE_3__ REDISMODULE_CTX_INIT ; 
 int /*<<< orphan*/  moduleFreeContext (TYPE_3__*) ; 
 int /*<<< orphan*/  resetClient (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_4__*) ; 

void unblockClientFromModule(client *c) {
    RedisModuleBlockedClient *bc = c->bpop.module_blocked_handle;

    /* Call the disconnection callback if any. */
    if (bc->disconnect_callback) {
        RedisModuleCtx ctx = REDISMODULE_CTX_INIT;
        ctx.blocked_privdata = bc->privdata;
        ctx.module = bc->module;
        ctx.client = bc->client;
        bc->disconnect_callback(&ctx,bc);
        moduleFreeContext(&ctx);
    }

    bc->client = NULL;
    /* Reset the client for a new query since, for blocking commands implemented
     * into modules, we do not it immediately after the command returns (and
     * the client blocks) in order to be still able to access the argument
     * vector from callbacks. */
    resetClient(c);
}