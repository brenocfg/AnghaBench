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
struct TYPE_2__ {int masterport; scalar_t__ repl_state; scalar_t__ master; int /*<<< orphan*/ * masterhost; } ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_EVENT_MASTER_LINK_CHANGE ; 
 int /*<<< orphan*/  REDISMODULE_EVENT_REPLICATION_ROLE_CHANGED ; 
 int /*<<< orphan*/  REDISMODULE_EVENT_REPLROLECHANGED_NOW_REPLICA ; 
 int /*<<< orphan*/  REDISMODULE_SUBEVENT_MASTER_LINK_DOWN ; 
 scalar_t__ REPL_STATE_CONNECT ; 
 scalar_t__ REPL_STATE_CONNECTED ; 
 int /*<<< orphan*/  cancelReplicationHandshake () ; 
 int /*<<< orphan*/  disconnectAllBlockedClients () ; 
 int /*<<< orphan*/  disconnectSlaves () ; 
 int /*<<< orphan*/  freeClient (scalar_t__) ; 
 int /*<<< orphan*/  moduleFireServerEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replicationCacheMasterUsingMyself () ; 
 int /*<<< orphan*/  replicationDiscardCachedMaster () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sdsnew (char*) ; 
 TYPE_1__ server ; 

void replicationSetMaster(char *ip, int port) {
    int was_master = server.masterhost == NULL;

    sdsfree(server.masterhost);
    server.masterhost = sdsnew(ip);
    server.masterport = port;
    if (server.master) {
        freeClient(server.master);
    }
    disconnectAllBlockedClients(); /* Clients blocked in master, now slave. */

    /* Force our slaves to resync with us as well. They may hopefully be able
     * to partially resync with us, but we can notify the replid change. */
    disconnectSlaves();
    cancelReplicationHandshake();
    /* Before destroying our master state, create a cached master using
     * our own parameters, to later PSYNC with the new master. */
    if (was_master) {
        replicationDiscardCachedMaster();
        replicationCacheMasterUsingMyself();
    }

    /* Fire the role change modules event. */
    moduleFireServerEvent(REDISMODULE_EVENT_REPLICATION_ROLE_CHANGED,
                          REDISMODULE_EVENT_REPLROLECHANGED_NOW_REPLICA,
                          NULL);

    /* Fire the master link modules event. */
    if (server.repl_state == REPL_STATE_CONNECTED)
        moduleFireServerEvent(REDISMODULE_EVENT_MASTER_LINK_CHANGE,
                              REDISMODULE_SUBEVENT_MASTER_LINK_DOWN,
                              NULL);

    server.repl_state = REPL_STATE_CONNECT;
}