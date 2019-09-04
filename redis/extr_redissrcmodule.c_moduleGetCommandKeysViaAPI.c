#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct redisCommand {scalar_t__ getkeys_proc; } ;
typedef  int /*<<< orphan*/  robj ;
struct TYPE_7__ {int /*<<< orphan*/  (* func ) (TYPE_1__*,void**,int) ;int /*<<< orphan*/  module; } ;
struct TYPE_6__ {int* keys_pos; int keys_count; int /*<<< orphan*/  flags; int /*<<< orphan*/ * client; int /*<<< orphan*/  module; } ;
typedef  TYPE_1__ RedisModuleCtx ;
typedef  TYPE_2__ RedisModuleCommandProxy ;

/* Variables and functions */
 TYPE_1__ REDISMODULE_CTX_INIT ; 
 int /*<<< orphan*/  REDISMODULE_CTX_KEYS_POS_REQUEST ; 
 int /*<<< orphan*/  moduleFreeContext (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,void**,int) ; 

int *moduleGetCommandKeysViaAPI(struct redisCommand *cmd, robj **argv, int argc, int *numkeys) {
    RedisModuleCommandProxy *cp = (void*)(unsigned long)cmd->getkeys_proc;
    RedisModuleCtx ctx = REDISMODULE_CTX_INIT;

    ctx.module = cp->module;
    ctx.client = NULL;
    ctx.flags |= REDISMODULE_CTX_KEYS_POS_REQUEST;
    cp->func(&ctx,(void**)argv,argc);
    int *res = ctx.keys_pos;
    if (numkeys) *numkeys = ctx.keys_count;
    moduleFreeContext(&ctx);
    return res;
}