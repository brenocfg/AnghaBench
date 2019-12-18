#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ numslots; int flags; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; struct TYPE_9__* slaveof; } ;
typedef  TYPE_1__ clusterNode ;

/* Variables and functions */
 int CLUSTER_NODE_MASTER ; 
 int CLUSTER_NODE_MIGRATE_TO ; 
 int CLUSTER_NODE_SLAVE ; 
 int /*<<< orphan*/  clusterCloseAllSlots () ; 
 int /*<<< orphan*/  clusterNodeAddSlave (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  clusterNodeRemoveSlave (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* myself ; 
 scalar_t__ nodeIsMaster (TYPE_1__*) ; 
 int /*<<< orphan*/  replicationSetMaster (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetManualFailover () ; 
 int /*<<< orphan*/  serverAssert (int) ; 

void clusterSetMaster(clusterNode *n) {
    serverAssert(n != myself);
    serverAssert(myself->numslots == 0);

    if (nodeIsMaster(myself)) {
        myself->flags &= ~(CLUSTER_NODE_MASTER|CLUSTER_NODE_MIGRATE_TO);
        myself->flags |= CLUSTER_NODE_SLAVE;
        clusterCloseAllSlots();
    } else {
        if (myself->slaveof)
            clusterNodeRemoveSlave(myself->slaveof,myself);
    }
    myself->slaveof = n;
    clusterNodeAddSlave(n,myself);
    replicationSetMaster(n->ip, n->port);
    resetManualFailover();
}