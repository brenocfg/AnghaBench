#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  list ;
struct TYPE_9__ {int slot; TYPE_3__* source; } ;
typedef  TYPE_2__ clusterManagerReshardTableItem ;
struct TYPE_10__ {float slots_count; int* slots; } ;
typedef  TYPE_3__ clusterManagerNode ;

/* Variables and functions */
 int CLUSTER_MANAGER_SLOTS ; 
 float ceil (float) ; 
 int /*<<< orphan*/  clusterManagerSlotCountCompareDesc ; 
 float floor (float) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * listCreate () ; 
 int listLength (int /*<<< orphan*/ *) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qsort (TYPE_3__**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_3__**) ; 
 void* zmalloc (int) ; 

__attribute__((used)) static list *clusterManagerComputeReshardTable(list *sources, int numslots) {
    list *moved = listCreate();
    int src_count = listLength(sources), i = 0, tot_slots = 0, j;
    clusterManagerNode **sorted = zmalloc(src_count * sizeof(*sorted));
    listIter li;
    listNode *ln;
    listRewind(sources, &li);
    while ((ln = listNext(&li)) != NULL) {
        clusterManagerNode *node = ln->value;
        tot_slots += node->slots_count;
        sorted[i++] = node;
    }
    qsort(sorted, src_count, sizeof(clusterManagerNode *),
          clusterManagerSlotCountCompareDesc);
    for (i = 0; i < src_count; i++) {
        clusterManagerNode *node = sorted[i];
        float n = ((float) numslots / tot_slots * node->slots_count);
        if (i == 0) n = ceil(n);
        else n = floor(n);
        int max = (int) n, count = 0;
        for (j = 0; j < CLUSTER_MANAGER_SLOTS; j++) {
            int slot = node->slots[j];
            if (!slot) continue;
            if (count >= max || (int)listLength(moved) >= numslots) break;
            clusterManagerReshardTableItem *item = zmalloc(sizeof(*item));
            item->source = node;
            item->slot = j;
            listAddNodeTail(moved, item);
            count++;
        }
    }
    zfree(sorted);
    return moved;
}