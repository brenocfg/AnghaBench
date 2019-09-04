#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * slaveof; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ clusterNode ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_NODE_MASTER ; 
 int /*<<< orphan*/  CLUSTER_NODE_MIGRATE_TO ; 
 int /*<<< orphan*/  CLUSTER_NODE_SLAVE ; 
 int CLUSTER_TODO_SAVE_CONFIG ; 
 int CLUSTER_TODO_UPDATE_STATE ; 
 int /*<<< orphan*/  clusterDoBeforeSleep (int) ; 
 int /*<<< orphan*/  clusterNodeRemoveSlave (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* myself ; 
 scalar_t__ nodeIsMaster (TYPE_1__*) ; 

void clusterSetNodeAsMaster(clusterNode *n) {
    if (nodeIsMaster(n)) return;

    if (n->slaveof) {
        clusterNodeRemoveSlave(n->slaveof,n);
        if (n != myself) n->flags |= CLUSTER_NODE_MIGRATE_TO;
    }
    n->flags &= ~CLUSTER_NODE_SLAVE;
    n->flags |= CLUSTER_NODE_MASTER;
    n->slaveof = NULL;

    /* Update config and state. */
    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                         CLUSTER_TODO_UPDATE_STATE);
}