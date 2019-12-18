#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t nb_items; size_t anchor_item; size_t page_size; size_t selected_item; int focus_item; int /*<<< orphan*/ * items; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LB_ITEMDATA ;
typedef  TYPE_1__ LB_DESCR ;
typedef  size_t INT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int HeapSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ISWIN31 ; 
 int /*<<< orphan*/  IS_MULTISELECT (TYPE_1__*) ; 
 int LB_ARRAY_GRANULARITY ; 
 int /*<<< orphan*/  LB_ERR ; 
 int /*<<< orphan*/  LB_OKAY ; 
 int /*<<< orphan*/  LISTBOX_DeleteItem (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  LISTBOX_InvalidateItems (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  LISTBOX_SetSelection (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LISTBOX_SetTopItem (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LISTBOX_UpdateScroll (TYPE_1__*) ; 
 int /*<<< orphan*/  RtlMoveMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT LISTBOX_RemoveItem( LB_DESCR *descr, INT index )
{
    LB_ITEMDATA *item;
    INT max_items;

    if ((index < 0) || (index >= descr->nb_items)) return LB_ERR;

    /* We need to invalidate the original rect instead of the updated one. */
    LISTBOX_InvalidateItems( descr, index );

    descr->nb_items--;
    LISTBOX_DeleteItem( descr, index );

    if (!descr->nb_items) return LB_OKAY;

    /* Remove the item */

    item = &descr->items[index];
    if (index < descr->nb_items)
        RtlMoveMemory( item, item + 1,
                       (descr->nb_items - index) * sizeof(LB_ITEMDATA) );
    if (descr->anchor_item == descr->nb_items) descr->anchor_item--;

    /* Shrink the item array if possible */

    max_items = HeapSize( GetProcessHeap(), 0, descr->items ) / sizeof(LB_ITEMDATA);
    if (descr->nb_items < max_items - 2*LB_ARRAY_GRANULARITY)
    {
        max_items -= LB_ARRAY_GRANULARITY;
        item = HeapReAlloc( GetProcessHeap(), 0, descr->items,
                            max_items * sizeof(LB_ITEMDATA) );
        if (item) descr->items = item;
    }
    /* Repaint the items */

    LISTBOX_UpdateScroll( descr );
    /* if we removed the scrollbar, reset the top of the list
      (correct for owner-drawn ???) */
    if (descr->nb_items == descr->page_size)
        LISTBOX_SetTopItem( descr, 0, TRUE );

    /* Move selection and focused item */
    if (!IS_MULTISELECT(descr))
    {
        if (index == descr->selected_item)
            descr->selected_item = -1;
        else if (index < descr->selected_item)
        {
            descr->selected_item--;
            if (ISWIN31) /* win 31 do not change the selected item number */
               LISTBOX_SetSelection( descr, descr->selected_item + 1, TRUE, FALSE);
        }
    }

    if (descr->focus_item >= descr->nb_items)
    {
          descr->focus_item = descr->nb_items - 1;
          if (descr->focus_item < 0) descr->focus_item = 0;
    }
    return LB_OKAY;
}