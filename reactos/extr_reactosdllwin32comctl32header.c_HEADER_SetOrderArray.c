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
typedef  scalar_t__ UINT ;
struct TYPE_6__ {scalar_t__ uNumItem; size_t* order; int /*<<< orphan*/  hwndSelf; TYPE_1__* items; } ;
struct TYPE_5__ {size_t iOrder; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  size_t INT ;
typedef  TYPE_1__ HEADER_ITEM ;
typedef  TYPE_2__ HEADER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HEADER_SetItemBounds (TYPE_2__*) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 void* get_nextvalue (size_t*,size_t,size_t) ; 
 size_t has_duplicate (size_t*,size_t,size_t const) ; 
 int /*<<< orphan*/  header ; 

__attribute__((used)) static LRESULT
HEADER_SetOrderArray(HEADER_INFO *infoPtr, INT size, const INT *order)
{
    HEADER_ITEM *lpItem;
    INT i;

    if ((UINT)size != infoPtr->uNumItem)
      return FALSE;

    if (TRACE_ON(header))
    {
        TRACE("count=%d, order array={", size);
        for (i = 0; i < size; i++)
            TRACE("%d%c", order[i], i != size-1 ? ',' : '}');
        TRACE("\n");
    }

    for (i=0; i<size; i++)
    {
        if (order[i] >= size || order[i] < 0)
           /* on invalid index get next available */
           /* FIXME: if i==0 array item is out of range behaviour is
                     different, see tests */
           infoPtr->order[i] = get_nextvalue(infoPtr->order, i, size);
        else
        {
           INT j, dup;

           infoPtr->order[i] = order[i];
           j = i;
           /* remove duplicates */
           while ((dup = has_duplicate(infoPtr->order, j, order[j])) != -1)
           {
               INT next;

               next = get_nextvalue(infoPtr->order, j, size);
               infoPtr->order[dup] = next;
               j--;
           }
        }
    }
    /* sync with item data */
    for (i=0; i<size; i++)
    {
        lpItem = &infoPtr->items[infoPtr->order[i]];
        lpItem->iOrder = i;
    }
    HEADER_SetItemBounds(infoPtr);
    InvalidateRect(infoPtr->hwndSelf, NULL, FALSE);
    return TRUE;
}