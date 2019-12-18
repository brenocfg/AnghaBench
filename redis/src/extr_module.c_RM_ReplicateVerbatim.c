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
struct TYPE_9__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_8__ {TYPE_2__* client; } ;
struct TYPE_7__ {int /*<<< orphan*/  argc; int /*<<< orphan*/  argv; TYPE_1__* db; int /*<<< orphan*/  cmd; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ RedisModuleCtx ;

/* Variables and functions */
 int PROPAGATE_AOF ; 
 int PROPAGATE_REPL ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  alsoPropagate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ server ; 

int RM_ReplicateVerbatim(RedisModuleCtx *ctx) {
    alsoPropagate(ctx->client->cmd,ctx->client->db->id,
        ctx->client->argv,ctx->client->argc,
        PROPAGATE_AOF|PROPAGATE_REPL);
    server.dirty++;
    return REDISMODULE_OK;
}