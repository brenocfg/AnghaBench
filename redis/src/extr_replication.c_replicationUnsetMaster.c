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
struct TYPE_2__ {scalar_t__ repl_state; int slaveseldb; int /*<<< orphan*/  unixtime; int /*<<< orphan*/  repl_no_slaves_since; scalar_t__ master; int /*<<< orphan*/ * masterhost; } ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_EVENT_MASTER_LINK_CHANGE ; 
 int /*<<< orphan*/  REDISMODULE_EVENT_REPLICATION_ROLE_CHANGED ; 
 int /*<<< orphan*/  REDISMODULE_EVENT_REPLROLECHANGED_NOW_MASTER ; 
 int /*<<< orphan*/  REDISMODULE_SUBEVENT_MASTER_LINK_DOWN ; 
 scalar_t__ REPL_STATE_CONNECTED ; 
 scalar_t__ REPL_STATE_NONE ; 
 int /*<<< orphan*/  cancelReplicationHandshake () ; 
 int /*<<< orphan*/  disconnectSlaves () ; 
 int /*<<< orphan*/  freeClient (scalar_t__) ; 
 int /*<<< orphan*/  moduleFireServerEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replicationDiscardCachedMaster () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  shiftReplicationId () ; 

void replicationUnsetMaster(void) {
    if (server.masterhost == NULL) return; /* Nothing to do. */

    /* Fire the master link modules event. */
    if (server.repl_state == REPL_STATE_CONNECTED)
        moduleFireServerEvent(REDISMODULE_EVENT_MASTER_LINK_CHANGE,
                              REDISMODULE_SUBEVENT_MASTER_LINK_DOWN,
                              NULL);

    sdsfree(server.masterhost);
    server.masterhost = NULL;
    /* When a slave is turned into a master, the current replication ID
     * (that was inherited from the master at synchronization time) is
     * used as secondary ID up to the current offset, and a new replication
     * ID is created to continue with a new replication history. */
    shiftReplicationId();
    if (server.master) freeClient(server.master);
    replicationDiscardCachedMaster();
    cancelReplicationHandshake();
    /* Disconnecting all the slaves is required: we need to inform slaves
     * of the replication ID change (see shiftReplicationId() call). However
     * the slaves will be able to partially resync with us, so it will be
     * a very fast reconnection. */
    disconnectSlaves();
    server.repl_state = REPL_STATE_NONE;

    /* We need to make sure the new master will start the replication stream
     * with a SELECT statement. This is forced after a full resync, but
     * with PSYNC version 2, there is no need for full resync after a
     * master switch. */
    server.slaveseldb = -1;

    /* Once we turn from slave to master, we consider the starting time without
     * slaves (that is used to count the replication backlog time to live) as
     * starting from now. Otherwise the backlog will be freed after a
     * failover if slaves do not connect immediately. */
    server.repl_no_slaves_since = server.unixtime;

    /* Fire the role change modules event. */
    moduleFireServerEvent(REDISMODULE_EVENT_REPLICATION_ROLE_CHANGED,
                          REDISMODULE_EVENT_REPLROLECHANGED_NOW_MASTER,
                          NULL);
}