#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ uNumItem; int /*<<< orphan*/  hwndSelf; struct TYPE_5__* order; struct TYPE_5__* items; struct TYPE_5__* pszText; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ INT ;
typedef  TYPE_1__ HEADER_ITEM ;
typedef  TYPE_1__ HEADER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 

__attribute__((used)) static LRESULT
HEADER_NCDestroy (HEADER_INFO *infoPtr)
{
    HEADER_ITEM *lpItem;
    INT nItem;

    if (infoPtr->items) {
        lpItem = infoPtr->items;
        for (nItem = 0; nItem < infoPtr->uNumItem; nItem++, lpItem++)
            heap_free(lpItem->pszText);
        heap_free(infoPtr->items);
    }

    heap_free(infoPtr->order);

    SetWindowLongPtrW (infoPtr->hwndSelf, 0, 0);
    heap_free(infoPtr);

    return 0;
}