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
typedef  int /*<<< orphan*/  robj ;
struct TYPE_9__ {TYPE_4__* module_blocked_handle; } ;
struct TYPE_10__ {int /*<<< orphan*/  argc; scalar_t__ argv; TYPE_1__ bpop; } ;
typedef  TYPE_2__ client ;
struct TYPE_12__ {scalar_t__ (* reply_callback ) (TYPE_3__*,void**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  client; int /*<<< orphan*/  module; int /*<<< orphan*/  privdata; scalar_t__ unblocked; } ;
struct TYPE_11__ {TYPE_4__* blocked_client; int /*<<< orphan*/  client; int /*<<< orphan*/  module; int /*<<< orphan*/  blocked_privdata; int /*<<< orphan*/ * blocked_ready_key; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ RedisModuleCtx ;
typedef  TYPE_4__ RedisModuleBlockedClient ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_CTX_BLOCKED_REPLY ; 
 TYPE_3__ REDISMODULE_CTX_INIT ; 
 int REDISMODULE_ERR ; 
 scalar_t__ REDISMODULE_OK ; 
 int /*<<< orphan*/  moduleFreeContext (TYPE_3__*) ; 
 scalar_t__ stub1 (TYPE_3__*,void**,int /*<<< orphan*/ ) ; 

int moduleTryServeClientBlockedOnKey(client *c, robj *key) {
    int served = 0;
    RedisModuleBlockedClient *bc = c->bpop.module_blocked_handle;
    /* Protect against re-processing: don't serve clients that are already
     * in the unblocking list for any reason (including RM_UnblockClient()
     * explicit call). */
    if (bc->unblocked) return REDISMODULE_ERR;
    RedisModuleCtx ctx = REDISMODULE_CTX_INIT;
    ctx.flags |= REDISMODULE_CTX_BLOCKED_REPLY;
    ctx.blocked_ready_key = key;
    ctx.blocked_privdata = bc->privdata;
    ctx.module = bc->module;
    ctx.client = bc->client;
    ctx.blocked_client = bc;
    if (bc->reply_callback(&ctx,(void**)c->argv,c->argc) == REDISMODULE_OK)
        served = 1;
    moduleFreeContext(&ctx);
    return served;
}