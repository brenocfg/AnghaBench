#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * sds ;
struct TYPE_4__ {int /*<<< orphan*/ * value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  clusterManagerNode ;
struct TYPE_5__ {int /*<<< orphan*/ * errors; int /*<<< orphan*/ * nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/ * clusterManagerUncoveredSlots ; 
 TYPE_3__ cluster_manager ; 
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeClusterManagerNode (int /*<<< orphan*/ *) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void freeClusterManager(void) {
    listIter li;
    listNode *ln;
    if (cluster_manager.nodes != NULL) {
        listRewind(cluster_manager.nodes,&li);
        while ((ln = listNext(&li)) != NULL) {
            clusterManagerNode *n = ln->value;
            freeClusterManagerNode(n);
        }
        listRelease(cluster_manager.nodes);
        cluster_manager.nodes = NULL;
    }
    if (cluster_manager.errors != NULL) {
        listRewind(cluster_manager.errors,&li);
        while ((ln = listNext(&li)) != NULL) {
            sds err = ln->value;
            sdsfree(err);
        }
        listRelease(cluster_manager.errors);
        cluster_manager.errors = NULL;
    }
    if (clusterManagerUncoveredSlots != NULL)
        dictRelease(clusterManagerUncoveredSlots);
}