#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_6__ {scalar_t__* slots; } ;
typedef  TYPE_2__ clusterManagerNode ;
struct TYPE_7__ {int /*<<< orphan*/ * nodes; } ;

/* Variables and functions */
 int CLUSTER_MANAGER_SLOTS ; 
 TYPE_4__ cluster_manager ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int clusterManagerGetCoveredSlots(char *all_slots) {
    if (cluster_manager.nodes == NULL) return 0;
    listIter li;
    listNode *ln;
    listRewind(cluster_manager.nodes, &li);
    int totslots = 0, i;
    while ((ln = listNext(&li)) != NULL) {
        clusterManagerNode *node = ln->value;
        for (i = 0; i < CLUSTER_MANAGER_SLOTS; i++) {
            if (node->slots[i] && !all_slots[i]) {
                all_slots[i] = 1;
                totslots++;
            }
        }
    }
    return totslots;
}