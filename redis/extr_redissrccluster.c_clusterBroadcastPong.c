#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_9__ {int /*<<< orphan*/  link; struct TYPE_9__* slaveof; } ;
typedef  TYPE_2__ clusterNode ;
struct TYPE_10__ {TYPE_1__* cluster; } ;
struct TYPE_8__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTERMSG_TYPE_PONG ; 
 int CLUSTER_BROADCAST_LOCAL_SLAVES ; 
 int /*<<< orphan*/  clusterSendPing (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetSafeIterator (int /*<<< orphan*/ ) ; 
 TYPE_2__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 TYPE_2__* myself ; 
 scalar_t__ nodeInHandshake (TYPE_2__*) ; 
 scalar_t__ nodeIsSlave (TYPE_2__*) ; 
 TYPE_3__ server ; 

void clusterBroadcastPong(int target) {
    dictIterator *di;
    dictEntry *de;

    di = dictGetSafeIterator(server.cluster->nodes);
    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetVal(de);

        if (!node->link) continue;
        if (node == myself || nodeInHandshake(node)) continue;
        if (target == CLUSTER_BROADCAST_LOCAL_SLAVES) {
            int local_slave =
                nodeIsSlave(node) && node->slaveof &&
                (node->slaveof == myself || node->slaveof == myself->slaveof);
            if (!local_slave) continue;
        }
        clusterSendPing(node->link,CLUSTERMSG_TYPE_PONG);
    }
    dictReleaseIterator(di);
}