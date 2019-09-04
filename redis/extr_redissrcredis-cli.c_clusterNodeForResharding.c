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
struct TYPE_5__ {int flags; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ clusterManagerNode ;

/* Variables and functions */
 int CLUSTER_MANAGER_FLAG_SLAVE ; 
 int /*<<< orphan*/  clusterManagerLogErr (char const*,...) ; 
 TYPE_1__* clusterManagerNodeByName (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static clusterManagerNode *clusterNodeForResharding(char *id,
                                                    clusterManagerNode *target,
                                                    int *raise_err)
{
    clusterManagerNode *node = NULL;
    const char *invalid_node_msg = "*** The specified node (%s) is not known "
                                   "or not a master, please retry.\n";
    node = clusterManagerNodeByName(id);
    *raise_err = 0;
    if (!node || node->flags & CLUSTER_MANAGER_FLAG_SLAVE) {
        clusterManagerLogErr(invalid_node_msg, id);
        *raise_err = 1;
        return NULL;
    } else if (node != NULL && target != NULL) {
        if (!strcmp(node->name, target->name)) {
            clusterManagerLogErr( "*** It is not possible to use "
                                  "the target node as "
                                  "source node.\n");
            return NULL;
        }
    }
    return node;
}