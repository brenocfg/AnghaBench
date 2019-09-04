#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int mstime_t ;
struct TYPE_7__ {scalar_t__ numslots; int fail_time; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ clusterNode ;
struct TYPE_8__ {int cluster_node_timeout; } ;

/* Variables and functions */
 int CLUSTER_FAIL_UNDO_TIME_MULT ; 
 int /*<<< orphan*/  CLUSTER_NODE_FAIL ; 
 int CLUSTER_TODO_SAVE_CONFIG ; 
 int CLUSTER_TODO_UPDATE_STATE ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  clusterDoBeforeSleep (int) ; 
 int mstime () ; 
 int /*<<< orphan*/  nodeFailed (TYPE_1__*) ; 
 scalar_t__ nodeIsMaster (TYPE_1__*) ; 
 scalar_t__ nodeIsSlave (TYPE_1__*) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

void clearNodeFailureIfNeeded(clusterNode *node) {
    mstime_t now = mstime();

    serverAssert(nodeFailed(node));

    /* For slaves we always clear the FAIL flag if we can contact the
     * node again. */
    if (nodeIsSlave(node) || node->numslots == 0) {
        serverLog(LL_NOTICE,
            "Clear FAIL state for node %.40s: %s is reachable again.",
                node->name,
                nodeIsSlave(node) ? "replica" : "master without slots");
        node->flags &= ~CLUSTER_NODE_FAIL;
        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
    }

    /* If it is a master and...
     * 1) The FAIL state is old enough.
     * 2) It is yet serving slots from our point of view (not failed over).
     * Apparently no one is going to fix these slots, clear the FAIL flag. */
    if (nodeIsMaster(node) && node->numslots > 0 &&
        (now - node->fail_time) >
        (server.cluster_node_timeout * CLUSTER_FAIL_UNDO_TIME_MULT))
    {
        serverLog(LL_NOTICE,
            "Clear FAIL state for node %.40s: is reachable again and nobody is serving its slots after some time.",
                node->name);
        node->flags &= ~CLUSTER_NODE_FAIL;
        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
    }
}