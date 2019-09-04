#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* module_blocked_handle; } ;
struct TYPE_10__ {int /*<<< orphan*/  argc; scalar_t__ argv; TYPE_1__ bpop; } ;
typedef  TYPE_2__ client ;
struct TYPE_12__ {int /*<<< orphan*/ * disconnect_callback; int /*<<< orphan*/  (* timeout_callback ) (TYPE_3__*,void**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  client; int /*<<< orphan*/  module; } ;
struct TYPE_11__ {TYPE_4__* blocked_client; int /*<<< orphan*/  client; int /*<<< orphan*/  module; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ RedisModuleCtx ;
typedef  TYPE_4__ RedisModuleBlockedClient ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_CTX_BLOCKED_TIMEOUT ; 
 TYPE_3__ REDISMODULE_CTX_INIT ; 
 int /*<<< orphan*/  moduleFreeContext (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,void**,int /*<<< orphan*/ ) ; 

void moduleBlockedClientTimedOut(client *c) {
    RedisModuleBlockedClient *bc = c->bpop.module_blocked_handle;
    RedisModuleCtx ctx = REDISMODULE_CTX_INIT;
    ctx.flags |= REDISMODULE_CTX_BLOCKED_TIMEOUT;
    ctx.module = bc->module;
    ctx.client = bc->client;
    ctx.blocked_client = bc;
    bc->timeout_callback(&ctx,(void**)c->argv,c->argc);
    moduleFreeContext(&ctx);
    /* For timeout events, we do not want to call the disconnect callback,
     * because the blocked client will be automatically disconnected in
     * this case, and the user can still hook using the timeout callback. */
    bc->disconnect_callback = NULL;
}