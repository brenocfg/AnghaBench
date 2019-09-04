#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  link; } ;
typedef  TYPE_2__ clusterNode ;
struct TYPE_7__ {TYPE_1__* cluster; } ;
struct TYPE_5__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int CLUSTER_NODE_HANDSHAKE ; 
 int CLUSTER_NODE_MYSELF ; 
 int /*<<< orphan*/  clusterSendMessage (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/ * dictGetSafeIterator (int /*<<< orphan*/ ) ; 
 TYPE_2__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 TYPE_3__ server ; 

void clusterBroadcastMessage(void *buf, size_t len) {
    dictIterator *di;
    dictEntry *de;

    di = dictGetSafeIterator(server.cluster->nodes);
    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetVal(de);

        if (!node->link) continue;
        if (node->flags & (CLUSTER_NODE_MYSELF|CLUSTER_NODE_HANDSHAKE))
            continue;
        clusterSendMessage(node->link,buf,len);
    }
    dictReleaseIterator(di);
}