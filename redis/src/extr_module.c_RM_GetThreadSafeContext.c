#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  empty ;
struct TYPE_15__ {int /*<<< orphan*/  id; } ;
struct TYPE_14__ {TYPE_1__* client; int /*<<< orphan*/  dbid; int /*<<< orphan*/  module; } ;
struct TYPE_13__ {TYPE_5__* client; int /*<<< orphan*/  flags; int /*<<< orphan*/  module; TYPE_3__* blocked_client; } ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ RedisModuleCtx ;
typedef  TYPE_3__ RedisModuleBlockedClient ;

/* Variables and functions */
 TYPE_2__ REDISMODULE_CTX_INIT ; 
 int /*<<< orphan*/  REDISMODULE_CTX_THREAD_SAFE ; 
 TYPE_5__* createClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  selectDb (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* zmalloc (int) ; 

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
    ctx->client = createClient(NULL);
    if (bc) {
        selectDb(ctx->client,bc->dbid);
        if (bc->client) ctx->client->id = bc->client->id;
    }
    return ctx;
}