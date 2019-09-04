#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  clusterNode ;
struct TYPE_5__ {int /*<<< orphan*/ * slaveof; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_BROADCAST_ALL ; 
 int CLUSTER_SLOTS ; 
 int /*<<< orphan*/  clusterAddSlot (TYPE_1__*,int) ; 
 int /*<<< orphan*/  clusterBroadcastPong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterDelSlot (int) ; 
 scalar_t__ clusterNodeGetSlotBit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clusterSaveConfigOrDie (int) ; 
 int /*<<< orphan*/  clusterSetNodeAsMaster (TYPE_1__*) ; 
 int /*<<< orphan*/  clusterUpdateState () ; 
 TYPE_1__* myself ; 
 scalar_t__ nodeIsMaster (TYPE_1__*) ; 
 int /*<<< orphan*/  replicationUnsetMaster () ; 
 int /*<<< orphan*/  resetManualFailover () ; 

void clusterFailoverReplaceYourMaster(void) {
    int j;
    clusterNode *oldmaster = myself->slaveof;

    if (nodeIsMaster(myself) || oldmaster == NULL) return;

    /* 1) Turn this node into a master. */
    clusterSetNodeAsMaster(myself);
    replicationUnsetMaster();

    /* 2) Claim all the slots assigned to our master. */
    for (j = 0; j < CLUSTER_SLOTS; j++) {
        if (clusterNodeGetSlotBit(oldmaster,j)) {
            clusterDelSlot(j);
            clusterAddSlot(myself,j);
        }
    }

    /* 3) Update state and save config. */
    clusterUpdateState();
    clusterSaveConfigOrDie(1);

    /* 4) Pong all the other nodes so that they can update the state
     *    accordingly and detect that we switched to master role. */
    clusterBroadcastPong(CLUSTER_BROADCAST_ALL);

    /* 5) If there was a manual failover in progress, clear the state. */
    resetManualFailover();
}