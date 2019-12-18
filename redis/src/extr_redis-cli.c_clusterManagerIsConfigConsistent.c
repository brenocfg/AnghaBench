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
struct TYPE_5__ {int /*<<< orphan*/ * nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/ * clusterManagerGetConfigSignature (int /*<<< orphan*/ *) ; 
 TYPE_3__ cluster_manager ; 
 int listLength (int /*<<< orphan*/ *) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdscmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int clusterManagerIsConfigConsistent(void) {
    if (cluster_manager.nodes == NULL) return 0;
    int consistent = (listLength(cluster_manager.nodes) <= 1);
    // If the Cluster has only one node, it's always consistent
    if (consistent) return 1;
    sds first_cfg = NULL;
    listIter li;
    listNode *ln;
    listRewind(cluster_manager.nodes, &li);
    while ((ln = listNext(&li)) != NULL) {
        clusterManagerNode *node = ln->value;
        sds cfg = clusterManagerGetConfigSignature(node);
        if (cfg == NULL) {
            consistent = 0;
            break;
        }
        if (first_cfg == NULL) first_cfg = cfg;
        else {
            consistent = !sdscmp(first_cfg, cfg);
            sdsfree(cfg);
            if (!consistent) break;
        }
    }
    if (first_cfg != NULL) sdsfree(first_cfg);
    return consistent;
}