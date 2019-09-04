#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  clusterNode ;
struct TYPE_2__ {int cluster_node_count; int /*<<< orphan*/ ** cluster_nodes; } ;

/* Variables and functions */
 TYPE_1__ config ; 
 int /*<<< orphan*/  freeClusterNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void freeClusterNodes() {
    int i = 0;
    for (; i < config.cluster_node_count; i++) {
        clusterNode *n = config.cluster_nodes[i];
        if (n) freeClusterNode(n);
    }
    zfree(config.cluster_nodes);
    config.cluster_nodes = NULL;
}