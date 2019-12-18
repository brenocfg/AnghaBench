#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void** Distance; struct TYPE_6__** Next; int /*<<< orphan*/  Element; } ;
struct TYPE_7__ {size_t MaximumLevel; void* NodeCount; TYPE_1__* (* AllocateRoutine ) (int) ;TYPE_1__ Head; } ;
typedef  int /*<<< orphan*/  SKIPLIST_NODE ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PSKIPLIST_NODE ;
typedef  TYPE_2__* PSKIPLIST ;
typedef  void* DWORD ;
typedef  size_t CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 size_t _GetRandomLevel () ; 
 TYPE_1__* stub1 (int) ; 

__attribute__((used)) static BOOL
_InsertElementSkiplistWithInformation(PSKIPLIST Skiplist, PVOID Element, PSKIPLIST_NODE* pUpdate, DWORD* dwDistance)
{
    CHAR chNewLevel;
    CHAR i;
    PSKIPLIST_NODE pNode;

    // Get the highest level, on which the node shall be inserted.
    chNewLevel = _GetRandomLevel();

    // Check if the new level is higher than the maximum level we currently have in the Skiplist.
    if (chNewLevel > Skiplist->MaximumLevel)
    {
        // It is, so we also need to insert the new node right after the Head node on some levels.
        // These are the levels higher than the current maximum level up to the new level.
        // We also need to set the distance of these elements to the new node count to account for the calculations below.
        for (i = Skiplist->MaximumLevel + 1; i <= chNewLevel; i++)
        {
            pUpdate[i] = &Skiplist->Head;
            pUpdate[i]->Distance[i] = Skiplist->NodeCount + 1;
        }

        // The new level is the new maximum level of the entire Skiplist.
        Skiplist->MaximumLevel = chNewLevel;
    }

    // Finally create our new Skiplist node.
    pNode = Skiplist->AllocateRoutine(sizeof(SKIPLIST_NODE));
    if (!pNode)
        return FALSE;

    pNode->Element = Element;

    // For each used level, insert us between the saved node for this level and its current next node.
    for (i = 0; i <= chNewLevel; i++)
    {
        pNode->Next[i] = pUpdate[i]->Next[i];
        pUpdate[i]->Next[i] = pNode;

        // We know the walked distance in this level: dwDistance[i]
        // We also know the element index of the new node: dwDistance[0]
        // The new node's distance is now the walked distance in this level plus the difference between the saved node's distance and the element index.
        pNode->Distance[i] = dwDistance[i] + (pUpdate[i]->Distance[i] - dwDistance[0]);

        // The saved node's distance is now the element index plus one (to account for the added node) minus the walked distance in this level.
        pUpdate[i]->Distance[i] = dwDistance[0] + 1 - dwDistance[i];
    }

    // For all levels above the new node's level, we need to increment the distance, because we've just added our new node.
    for (i = chNewLevel + 1; i <= Skiplist->MaximumLevel; i++)
        ++pUpdate[i]->Distance[i];

    // We've successfully added a node :)
    ++Skiplist->NodeCount;
    return TRUE;
}