#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_7__ {int flags; TYPE_1__* db; } ;
typedef  TYPE_2__ client ;
struct TYPE_9__ {int /*<<< orphan*/  execCommand; } ;
struct TYPE_8__ {int flags; TYPE_2__* client; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ RedisModuleCtx ;

/* Variables and functions */
 int CLIENT_LUA ; 
 int PROPAGATE_AOF ; 
 int PROPAGATE_REPL ; 
 int REDISMODULE_CTX_MULTI_EMITTED ; 
 int /*<<< orphan*/  alsoPropagate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int) ; 
 int /*<<< orphan*/ * createStringObject (char*,int) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 TYPE_4__ server ; 

void moduleHandlePropagationAfterCommandCallback(RedisModuleCtx *ctx) {
    client *c = ctx->client;

    if (c->flags & CLIENT_LUA) return;

    /* Handle the replication of the final EXEC, since whatever a command
     * emits is always wrapped around MULTI/EXEC. */
    if (ctx->flags & REDISMODULE_CTX_MULTI_EMITTED) {
        robj *propargv[1];
        propargv[0] = createStringObject("EXEC",4);
        alsoPropagate(server.execCommand,c->db->id,propargv,1,
            PROPAGATE_AOF|PROPAGATE_REPL);
        decrRefCount(propargv[0]);
    }
}