#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
struct TYPE_8__ {TYPE_2__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  list ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  dict ;
struct TYPE_9__ {int /*<<< orphan*/  node_addr; int /*<<< orphan*/  node_name; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
typedef  TYPE_2__ clusterManagerNode ;
typedef  TYPE_2__ clusterManagerLink ;
struct TYPE_10__ {int /*<<< orphan*/ * nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/ * clusterManagerGetDisconnectedLinks (TYPE_2__*) ; 
 int /*<<< orphan*/  clusterManagerLinkDictType ; 
 TYPE_6__ cluster_manager ; 
 int /*<<< orphan*/  dictAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * listCreate () ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdscatfmt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 

__attribute__((used)) static dict *clusterManagerGetLinkStatus(void) {
    if (cluster_manager.nodes == NULL) return NULL;
    dict *status = dictCreate(&clusterManagerLinkDictType, NULL);
    listIter li;
    listNode *ln;
    listRewind(cluster_manager.nodes, &li);
    while ((ln = listNext(&li)) != NULL) {
        clusterManagerNode *node = ln->value;
        list *links = clusterManagerGetDisconnectedLinks(node);
        if (links) {
            listIter lli;
            listNode *lln;
            listRewind(links, &lli);
            while ((lln = listNext(&lli)) != NULL) {
                clusterManagerLink *link = lln->value;
                list *from = NULL;
                dictEntry *entry = dictFind(status, link->node_addr);
                if (entry) from = dictGetVal(entry);
                else {
                    from = listCreate();
                    dictAdd(status, sdsdup(link->node_addr), from);
                }
                sds myaddr = sdsempty();
                myaddr = sdscatfmt(myaddr, "%s:%u", node->ip, node->port);
                listAddNodeTail(from, myaddr);
                sdsfree(link->node_name);
                sdsfree(link->node_addr);
                zfree(link);
            }
            listRelease(links);
        }
    }
    return status;
}