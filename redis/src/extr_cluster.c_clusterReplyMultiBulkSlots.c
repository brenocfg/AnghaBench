#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_9__ {scalar_t__ numslots; int port; int numslaves; TYPE_5__** slaves; int /*<<< orphan*/  name; int /*<<< orphan*/  ip; } ;
typedef  TYPE_2__ clusterNode ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_11__ {int port; int /*<<< orphan*/  name; int /*<<< orphan*/  ip; } ;
struct TYPE_10__ {TYPE_1__* cluster; } ;
struct TYPE_8__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_NAMELEN ; 
 int CLUSTER_SLOTS ; 
 int /*<<< orphan*/  addReplyArrayLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkCString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* addReplyDeferredLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyLongLong (int /*<<< orphan*/ *,int) ; 
 int clusterNodeGetSlotBit (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * dictGetSafeIterator (int /*<<< orphan*/ ) ; 
 TYPE_2__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 scalar_t__ nodeFailed (TYPE_5__*) ; 
 int /*<<< orphan*/  nodeIsMaster (TYPE_2__*) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  setDeferredArrayLen (int /*<<< orphan*/ *,void*,int) ; 

void clusterReplyMultiBulkSlots(client *c) {
    /* Format: 1) 1) start slot
     *            2) end slot
     *            3) 1) master IP
     *               2) master port
     *               3) node ID
     *            4) 1) replica IP
     *               2) replica port
     *               3) node ID
     *           ... continued until done
     */

    int num_masters = 0;
    void *slot_replylen = addReplyDeferredLen(c);

    dictEntry *de;
    dictIterator *di = dictGetSafeIterator(server.cluster->nodes);
    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetVal(de);
        int j = 0, start = -1;

        /* Skip slaves (that are iterated when producing the output of their
         * master) and  masters not serving any slot. */
        if (!nodeIsMaster(node) || node->numslots == 0) continue;

        for (j = 0; j < CLUSTER_SLOTS; j++) {
            int bit, i;

            if ((bit = clusterNodeGetSlotBit(node,j)) != 0) {
                if (start == -1) start = j;
            }
            if (start != -1 && (!bit || j == CLUSTER_SLOTS-1)) {
                int nested_elements = 3; /* slots (2) + master addr (1). */
                void *nested_replylen = addReplyDeferredLen(c);

                if (bit && j == CLUSTER_SLOTS-1) j++;

                /* If slot exists in output map, add to it's list.
                 * else, create a new output map for this slot */
                if (start == j-1) {
                    addReplyLongLong(c, start); /* only one slot; low==high */
                    addReplyLongLong(c, start);
                } else {
                    addReplyLongLong(c, start); /* low */
                    addReplyLongLong(c, j-1);   /* high */
                }
                start = -1;

                /* First node reply position is always the master */
                addReplyArrayLen(c, 3);
                addReplyBulkCString(c, node->ip);
                addReplyLongLong(c, node->port);
                addReplyBulkCBuffer(c, node->name, CLUSTER_NAMELEN);

                /* Remaining nodes in reply are replicas for slot range */
                for (i = 0; i < node->numslaves; i++) {
                    /* This loop is copy/pasted from clusterGenNodeDescription()
                     * with modifications for per-slot node aggregation */
                    if (nodeFailed(node->slaves[i])) continue;
                    addReplyArrayLen(c, 3);
                    addReplyBulkCString(c, node->slaves[i]->ip);
                    addReplyLongLong(c, node->slaves[i]->port);
                    addReplyBulkCBuffer(c, node->slaves[i]->name, CLUSTER_NAMELEN);
                    nested_elements++;
                }
                setDeferredArrayLen(c, nested_replylen, nested_elements);
                num_masters++;
            }
        }
    }
    dictReleaseIterator(di);
    setDeferredArrayLen(c, slot_replylen, num_masters);
}