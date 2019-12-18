#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_9__ {int target; int /*<<< orphan*/  argc; int /*<<< orphan*/  argv; int /*<<< orphan*/  dbid; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_2__ redisOp ;
struct TYPE_10__ {int flags; TYPE_1__* db; } ;
typedef  TYPE_3__ client ;
struct TYPE_13__ {int numops; TYPE_2__* ops; } ;
struct TYPE_12__ {TYPE_6__ also_propagate; int /*<<< orphan*/  execCommand; } ;
struct TYPE_11__ {int flags; TYPE_6__ saved_oparray; TYPE_3__* client; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_4__ RedisModuleCtx ;

/* Variables and functions */
 int CLIENT_LUA ; 
 int PROPAGATE_AOF ; 
 int PROPAGATE_REPL ; 
 int REDISMODULE_CTX_MODULE_COMMAND_CALL ; 
 int REDISMODULE_CTX_MULTI_EMITTED ; 
 int /*<<< orphan*/  alsoPropagate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int) ; 
 int /*<<< orphan*/ * createStringObject (char*,int) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  propagate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  redisOpArrayFree (TYPE_6__*) ; 
 TYPE_5__ server ; 

void moduleHandlePropagationAfterCommandCallback(RedisModuleCtx *ctx) {
    client *c = ctx->client;

    /* We don't need to do anything here if the context was never used
     * in order to propagate commands. */
    if (!(ctx->flags & REDISMODULE_CTX_MULTI_EMITTED)) return;

    if (c->flags & CLIENT_LUA) return;

    /* Handle the replication of the final EXEC, since whatever a command
     * emits is always wrapped around MULTI/EXEC. */
    robj *propargv[1];
    propargv[0] = createStringObject("EXEC",4);
    alsoPropagate(server.execCommand,c->db->id,propargv,1,
        PROPAGATE_AOF|PROPAGATE_REPL);
    decrRefCount(propargv[0]);

    /* If this is not a module command context (but is instead a simple
     * callback context), we have to handle directly the "also propagate"
     * array and emit it. In a module command call this will be handled
     * directly by call(). */
    if (!(ctx->flags & REDISMODULE_CTX_MODULE_COMMAND_CALL) &&
        server.also_propagate.numops)
    {
        for (int j = 0; j < server.also_propagate.numops; j++) {
            redisOp *rop = &server.also_propagate.ops[j];
            int target = rop->target;
            if (target)
                propagate(rop->cmd,rop->dbid,rop->argv,rop->argc,target);
        }
        redisOpArrayFree(&server.also_propagate);
        /* Restore the previous oparray in case of nexted use of the API. */
        server.also_propagate = ctx->saved_oparray;
    }
}