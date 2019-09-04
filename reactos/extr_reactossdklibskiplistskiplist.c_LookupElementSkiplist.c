#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * Element; struct TYPE_4__** Next; scalar_t__* Distance; } ;
struct TYPE_5__ {scalar_t__ MaximumLevel; scalar_t__ (* CompareRoutine ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;TYPE_1__ Head; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__* PSKIPLIST_NODE ;
typedef  TYPE_2__* PSKIPLIST ;
typedef  int /*<<< orphan*/ * PDWORD ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

PVOID
LookupElementSkiplist(PSKIPLIST Skiplist, PVOID Element, PDWORD ElementIndex)
{
    CHAR i;
    DWORD dwIndex = 0;
    PSKIPLIST_NODE pLastComparedNode = NULL;
    PSKIPLIST_NODE pNode = &Skiplist->Head;

    // Do the efficient lookup in Skiplists:
    //    * Start from the maximum level.
    //    * Walk through all nodes on this level that come before the node we're looking for.
    //    * When we have reached such a node, go down a level and continue there.
    //    * Repeat these steps till we're in level 0, right in front of the node we're looking for.
    for (i = Skiplist->MaximumLevel + 1; --i >= 0;)
    {
        while (pNode->Next[i] && pNode->Next[i] != pLastComparedNode && Skiplist->CompareRoutine(pNode->Next[i]->Element, Element) < 0)
        {
            dwIndex += pNode->Distance[i];
            pNode = pNode->Next[i];
        }   

        // Reduce the number of comparisons by not comparing the same node on different levels twice.
        pLastComparedNode = pNode->Next[i];
    }

    // We must be right in front of the node we're looking for now, otherwise it doesn't exist in the Skiplist at all.
    pNode = pNode->Next[0];
    if (!pNode || Skiplist->CompareRoutine(pNode->Element, Element) != 0)
    {
        // It hasn't been found, so there's nothing to return.
        return NULL;
    }

    // Return the index of the element if the caller is interested.
    if (ElementIndex)
        *ElementIndex = dwIndex;

    // Return the stored element of the found node.
    return pNode->Element;
}