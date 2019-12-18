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
typedef  int /*<<< orphan*/  sds ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  list ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  dict ;
struct TYPE_5__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int CLUSTER_JOIN_CHECK_AFTER ; 
 int /*<<< orphan*/ * clusterManagerGetLinkStatus () ; 
 int /*<<< orphan*/  clusterManagerIsConfigConsistent () ; 
 int /*<<< orphan*/  clusterManagerLogErr (char*,...) ; 
 TYPE_3__ cluster_manager ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictGetKey (int /*<<< orphan*/ *) ; 
 scalar_t__ dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listEmpty (int /*<<< orphan*/ *) ; 
 float listLength (int /*<<< orphan*/ ) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ parseClusterNodeAddress (int /*<<< orphan*/ ,char**,int*,int*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void clusterManagerWaitForClusterJoin(void) {
    printf("Waiting for the cluster to join\n");
    int counter = 0,
        check_after = CLUSTER_JOIN_CHECK_AFTER +
                      (int)(listLength(cluster_manager.nodes) * 0.15f);
    while(!clusterManagerIsConfigConsistent()) {
        printf(".");
        fflush(stdout);
        sleep(1);
        if (++counter > check_after) {
            dict *status = clusterManagerGetLinkStatus();
            dictIterator *iter = NULL;
            if (status != NULL && dictSize(status) > 0) {
                printf("\n");
                clusterManagerLogErr("Warning: %d node(s) may "
                                     "be unreachable\n", dictSize(status));
                iter = dictGetIterator(status);
                dictEntry *entry;
                while ((entry = dictNext(iter)) != NULL) {
                    sds nodeaddr = (sds) dictGetKey(entry);
                    char *node_ip = NULL;
                    int node_port = 0, node_bus_port = 0;
                    list *from = (list *) dictGetVal(entry);
                    if (parseClusterNodeAddress(nodeaddr, &node_ip,
                        &node_port, &node_bus_port) && node_bus_port) {
                        clusterManagerLogErr(" - The port %d of node %s may "
                                             "be unreachable from:\n",
                                             node_bus_port, node_ip);
                    } else {
                        clusterManagerLogErr(" - Node %s may be unreachable "
                                             "from:\n", nodeaddr);
                    }
                    listIter li;
                    listNode *ln;
                    listRewind(from, &li);
                    while ((ln = listNext(&li)) != NULL) {
                        sds from_addr = ln->value;
                        clusterManagerLogErr("   %s\n", from_addr);
                        sdsfree(from_addr);
                    }
                    clusterManagerLogErr("Cluster bus ports must be reachable "
                                         "by every node.\nRemember that "
                                         "cluster bus ports are different "
                                         "from standard instance ports.\n");
                    listEmpty(from);
                }
            }
            if (iter != NULL) dictReleaseIterator(iter);
            if (status != NULL) dictRelease(status);
            counter = 0;
        }
    }
    printf("\n");
}