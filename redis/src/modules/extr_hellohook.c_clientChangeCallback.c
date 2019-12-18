#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  port; int /*<<< orphan*/  addr; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/ * RedisModuleEvent ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;
typedef  TYPE_1__ RedisModuleClientInfo ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int /*<<< orphan*/ *) ; 
 scalar_t__ REDISMODULE_SUBEVENT_CLIENT_CHANGE_CONNECTED ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void clientChangeCallback(RedisModuleCtx *ctx, RedisModuleEvent e, uint64_t sub, void *data)
{
    REDISMODULE_NOT_USED(ctx);
    REDISMODULE_NOT_USED(e);

    RedisModuleClientInfo *ci = data;
    printf("Client %s event for client #%llu %s:%d\n",
        (sub == REDISMODULE_SUBEVENT_CLIENT_CHANGE_CONNECTED) ?
            "connection" : "disconnection",
        ci->id,ci->addr,ci->port);
}