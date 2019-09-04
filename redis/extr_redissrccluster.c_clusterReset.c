#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_11__ {int /*<<< orphan*/  name; scalar_t__ configEpoch; } ;
typedef  TYPE_2__ clusterNode ;
struct TYPE_12__ {TYPE_1__* cluster; } ;
struct TYPE_10__ {int /*<<< orphan*/  nodes; scalar_t__ lastVoteEpoch; scalar_t__ currentEpoch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_NAMELEN ; 
 int CLUSTER_SLOTS ; 
 int CLUSTER_TODO_FSYNC_CONFIG ; 
 int CLUSTER_TODO_SAVE_CONFIG ; 
 int CLUSTER_TODO_UPDATE_STATE ; 
 int /*<<< orphan*/  EMPTYDB_NO_FLAGS ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  clusterAddNode (TYPE_2__*) ; 
 int /*<<< orphan*/  clusterCloseAllSlots () ; 
 int /*<<< orphan*/  clusterDelNode (TYPE_2__*) ; 
 int /*<<< orphan*/  clusterDelSlot (int) ; 
 int /*<<< orphan*/  clusterDoBeforeSleep (int) ; 
 int /*<<< orphan*/  clusterSetNodeAsMaster (TYPE_2__*) ; 
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetSafeIterator (int /*<<< orphan*/ ) ; 
 TYPE_2__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emptyDb (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getRandomHexChars (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* myself ; 
 scalar_t__ nodeIsSlave (TYPE_2__*) ; 
 int /*<<< orphan*/  replicationUnsetMaster () ; 
 int /*<<< orphan*/  resetManualFailover () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnewlen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 

void clusterReset(int hard) {
    dictIterator *di;
    dictEntry *de;
    int j;

    /* Turn into master. */
    if (nodeIsSlave(myself)) {
        clusterSetNodeAsMaster(myself);
        replicationUnsetMaster();
        emptyDb(-1,EMPTYDB_NO_FLAGS,NULL);
    }

    /* Close slots, reset manual failover state. */
    clusterCloseAllSlots();
    resetManualFailover();

    /* Unassign all the slots. */
    for (j = 0; j < CLUSTER_SLOTS; j++) clusterDelSlot(j);

    /* Forget all the nodes, but myself. */
    di = dictGetSafeIterator(server.cluster->nodes);
    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetVal(de);

        if (node == myself) continue;
        clusterDelNode(node);
    }
    dictReleaseIterator(di);

    /* Hard reset only: set epochs to 0, change node ID. */
    if (hard) {
        sds oldname;

        server.cluster->currentEpoch = 0;
        server.cluster->lastVoteEpoch = 0;
        myself->configEpoch = 0;
        serverLog(LL_WARNING, "configEpoch set to 0 via CLUSTER RESET HARD");

        /* To change the Node ID we need to remove the old name from the
         * nodes table, change the ID, and re-add back with new name. */
        oldname = sdsnewlen(myself->name, CLUSTER_NAMELEN);
        dictDelete(server.cluster->nodes,oldname);
        sdsfree(oldname);
        getRandomHexChars(myself->name, CLUSTER_NAMELEN);
        clusterAddNode(myself);
        serverLog(LL_NOTICE,"Node hard reset, now I'm %.40s", myself->name);
    }

    /* Make sure to persist the new config and update the state. */
    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                         CLUSTER_TODO_UPDATE_STATE|
                         CLUSTER_TODO_FSYNC_CONFIG);
}