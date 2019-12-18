#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* Distance; struct TYPE_5__** Next; int /*<<< orphan*/ * Element; } ;
struct TYPE_6__ {int MaximumLevel; scalar_t__ (* CompareRoutine ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  NodeCount; TYPE_1__ Head; int /*<<< orphan*/  (* FreeRoutine ) (TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__* PSKIPLIST_NODE ;
typedef  TYPE_2__* PSKIPLIST ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */
 int SKIPLIST_LEVELS ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*) ; 

PVOID
DeleteElementSkiplist(PSKIPLIST Skiplist, PVOID Element)
{
    CHAR i;
    PSKIPLIST_NODE pLastComparedNode = NULL;
    PSKIPLIST_NODE pNode = &Skiplist->Head;
    PSKIPLIST_NODE pUpdate[SKIPLIST_LEVELS];
    PVOID pReturnValue;

    // Find the node on every currently used level, after which the node to be deleted must follow.
    // This can be done efficiently by starting from the maximum level and going down a level each time a position has been found.
    for (i = Skiplist->MaximumLevel + 1; --i >= 0;)
    {
        while (pNode->Next[i] && pNode->Next[i] != pLastComparedNode && Skiplist->CompareRoutine(pNode->Next[i]->Element, Element) < 0)
            pNode = pNode->Next[i];

        // Reduce the number of comparisons by not comparing the same node on different levels twice.
        pLastComparedNode = pNode->Next[i];
        pUpdate[i] = pNode;
    }

    // Check if the node we're looking for has been found.
    pNode = pNode->Next[0];
    if (!pNode || Skiplist->CompareRoutine(pNode->Element, Element) != 0)
    {
        // It hasn't been found, so there's nothing to delete.
        return NULL;
    }

    // Beginning at the lowest level, remove the node from each level of the list and merge distances.
    // We can stop as soon as we found the first level that doesn't contain the node.
    for (i = 0; i <= Skiplist->MaximumLevel && pUpdate[i]->Next[i] == pNode; i++)
    {
        pUpdate[i]->Distance[i] += pNode->Distance[i] - 1;
        pUpdate[i]->Next[i] = pNode->Next[i];
    }

    // Now decrement the distance of the corresponding node in levels higher than the deleted node's level to account for the deleted node.
    while (i <= Skiplist->MaximumLevel)
    {
        --pUpdate[i]->Distance[i];
        i++;
    }

    // Return the deleted element (so the caller can free it if necessary) and free the memory for the node itself (allocated by us).
    pReturnValue = pNode->Element;
    Skiplist->FreeRoutine(pNode);

    // Find all levels which now contain no more nodes and reduce the maximum level of the entire Skiplist accordingly.
    while (Skiplist->MaximumLevel > 0 && !Skiplist->Head.Next[Skiplist->MaximumLevel])
        --Skiplist->MaximumLevel;

    // We've successfully deleted the node :)
    --Skiplist->NodeCount;
    return pReturnValue;
}