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
struct TYPE_5__ {scalar_t__* Distance; struct TYPE_5__** Next; } ;
struct TYPE_6__ {scalar_t__ NodeCount; scalar_t__ MaximumLevel; TYPE_1__ Head; } ;
typedef  TYPE_1__* PSKIPLIST_NODE ;
typedef  TYPE_2__* PSKIPLIST ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */

PSKIPLIST_NODE
LookupNodeByIndexSkiplist(PSKIPLIST Skiplist, DWORD ElementIndex)
{
    CHAR i;
    DWORD dwIndex = 0;
    PSKIPLIST_NODE pNode = &Skiplist->Head;

    // The only way the node can't be found is when the index is out of range.
    if (ElementIndex >= Skiplist->NodeCount)
        return NULL;

    // Do the efficient lookup in Skiplists:
    //    * Start from the maximum level.
    //    * Walk through all nodes on this level that come before the node we're looking for.
    //    * When we have reached such a node, go down a level and continue there.
    //    * Repeat these steps till we're in level 0, right in front of the node we're looking for.
    for (i = Skiplist->MaximumLevel + 1; --i >= 0;)
    {
        // We compare with <= instead of < here, because the added distances make up a 1-based index while ElementIndex is zero-based,
        // so we have to jump one node further.
        while (pNode->Next[i] && dwIndex + pNode->Distance[i] <= ElementIndex)
        {
            dwIndex += pNode->Distance[i];
            pNode = pNode->Next[i];
        }
    }

    // We are right in front of the node we're looking for now.
    return pNode->Next[0];
}