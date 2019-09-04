#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  empty ;
struct TYPE_10__ {int /*<<< orphan*/  dbid; int /*<<< orphan*/  module; } ;
struct TYPE_9__ {int /*<<< orphan*/  client; int /*<<< orphan*/  flags; int /*<<< orphan*/  module; TYPE_2__* blocked_client; } ;
typedef  TYPE_1__ RedisModuleCtx ;
typedef  TYPE_2__ RedisModuleBlockedClient ;

/* Variables and functions */
 TYPE_1__ REDISMODULE_CTX_INIT ; 
 int /*<<< orphan*/  REDISMODULE_CTX_THREAD_SAFE ; 
 int /*<<< orphan*/  createClient (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  selectDb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* zmalloc (int) ; 

RedisModuleCtx *RM_GetThreadSafeContext(RedisModuleBlockedClient *bc) {
    RedisModuleCtx *ctx = zmalloc(sizeof(*ctx));
    RedisModuleCtx empty = REDISMODULE_CTX_INIT;
    memcpy(ctx,&empty,sizeof(empty));
    if (bc) {
        ctx->blocked_client = bc;
        ctx->module = bc->module;
    }
    ctx->flags |= REDISMODULE_CTX_THREAD_SAFE;
    /* Even when the context is associated with a blocked client, we can't
     * access it safely from another thread, so we create a fake client here
     * in order to keep things like the currently selected database and similar
     * things. */
    ctx->client = createClient(-1);
    if (bc) selectDb(ctx->client,bc->dbid);
    return ctx;
}