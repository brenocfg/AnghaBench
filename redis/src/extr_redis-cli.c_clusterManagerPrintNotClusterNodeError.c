#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
typedef  TYPE_1__ clusterManagerNode ;

/* Variables and functions */
 int /*<<< orphan*/  clusterManagerLogErr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void clusterManagerPrintNotClusterNodeError(clusterManagerNode *node,
                                                   char *err)
{
    char *msg = (err ? err : "is not configured as a cluster node.");
    clusterManagerLogErr("[ERR] Node %s:%d %s\n", node->ip, node->port, msg);
}