#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_7__ {int flags; int replicas_count; } ;
typedef  TYPE_2__ clusterManagerNode ;
struct TYPE_8__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int CLUSTER_MANAGER_FLAG_SLAVE ; 
 TYPE_4__ cluster_manager ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static clusterManagerNode *clusterManagerNodeWithLeastReplicas() {
    clusterManagerNode *node = NULL;
    int lowest_count = 0;
    listIter li;
    listNode *ln;
    listRewind(cluster_manager.nodes, &li);
    while ((ln = listNext(&li)) != NULL) {
        clusterManagerNode *n = ln->value;
        if (n->flags & CLUSTER_MANAGER_FLAG_SLAVE) continue;
        if (node == NULL || n->replicas_count < lowest_count) {
            node = n;
            lowest_count = n->replicas_count;
        }
    }
    return node;
}