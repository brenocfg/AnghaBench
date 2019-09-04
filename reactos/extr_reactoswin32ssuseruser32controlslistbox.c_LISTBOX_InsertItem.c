#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_19__ {int focus_item; int nb_items; int style; int item_height; int selected_item; int /*<<< orphan*/  self; int /*<<< orphan*/  owner; TYPE_2__* items; } ;
struct TYPE_18__ {int height; int /*<<< orphan*/  data; int /*<<< orphan*/  selected; scalar_t__ str; } ;
struct TYPE_17__ {int itemID; int itemHeight; int /*<<< orphan*/  itemData; int /*<<< orphan*/  CtlID; int /*<<< orphan*/  CtlType; } ;
typedef  TYPE_1__ MEASUREITEMSTRUCT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_2__ LB_ITEMDATA ;
typedef  TYPE_3__ LB_DESCR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int HeapSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ISWIN31 ; 
 int /*<<< orphan*/  IS_MULTISELECT (TYPE_3__*) ; 
 int /*<<< orphan*/  LBN_ERRSPACE ; 
 int LBS_OWNERDRAWVARIABLE ; 
 scalar_t__ LB_ARRAY_GRANULARITY ; 
 int /*<<< orphan*/  LB_ERR ; 
 int /*<<< orphan*/  LB_ERRSPACE ; 
 int /*<<< orphan*/  LB_OKAY ; 
 int /*<<< orphan*/  LISTBOX_InvalidateItems (TYPE_3__*,int) ; 
 int /*<<< orphan*/  LISTBOX_SetCaretIndex (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LISTBOX_SetSelection (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LISTBOX_UpdateScroll (TYPE_3__*) ; 
 int /*<<< orphan*/  ODT_LISTBOX ; 
 int /*<<< orphan*/  RtlMoveMemory (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  SEND_NOTIFICATION (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_MEASUREITEM ; 
 char* debugstr_w (scalar_t__) ; 

__attribute__((used)) static LRESULT LISTBOX_InsertItem( LB_DESCR *descr, INT index,
                                   LPWSTR str, ULONG_PTR data )
{
    LB_ITEMDATA *item;
    INT max_items;
    INT oldfocus = descr->focus_item;

    if (index == -1) index = descr->nb_items;
    else if ((index < 0) || (index > descr->nb_items)) return LB_ERR;
    if (!descr->items) max_items = 0;
    else max_items = HeapSize( GetProcessHeap(), 0, descr->items ) / sizeof(*item);
    if (descr->nb_items == max_items)
    {
        /* We need to grow the array */
        max_items += LB_ARRAY_GRANULARITY;
	if (descr->items)
    	    item = HeapReAlloc( GetProcessHeap(), 0, descr->items,
                                  max_items * sizeof(LB_ITEMDATA) );
	else
	    item = HeapAlloc( GetProcessHeap(), 0,
                                  max_items * sizeof(LB_ITEMDATA) );
        if (!item)
        {
            SEND_NOTIFICATION( descr, LBN_ERRSPACE );
            return LB_ERRSPACE;
        }
        descr->items = item;
    }

    /* Insert the item structure */

    item = &descr->items[index];
    if (index < descr->nb_items)
        RtlMoveMemory( item + 1, item,
                       (descr->nb_items - index) * sizeof(LB_ITEMDATA) );
    item->str      = str;
    item->data     = data;
    item->height   = 0;
    item->selected = FALSE;
    descr->nb_items++;

    /* Get item height */

    if (descr->style & LBS_OWNERDRAWVARIABLE)
    {
        MEASUREITEMSTRUCT mis;
        UINT id = (UINT)GetWindowLongPtrW( descr->self, GWLP_ID );

        mis.CtlType    = ODT_LISTBOX;
        mis.CtlID      = id;
        mis.itemID     = index;
        mis.itemData   = descr->items[index].data;
        mis.itemHeight = descr->item_height;
        SendMessageW( descr->owner, WM_MEASUREITEM, id, (LPARAM)&mis );
        item->height = mis.itemHeight ? mis.itemHeight : 1;
        TRACE("[%p]: measure item %d (%s) = %d\n",
              descr->self, index, str ? debugstr_w(str) : "", item->height );
    }

    /* Repaint the items */

    LISTBOX_UpdateScroll( descr );
    LISTBOX_InvalidateItems( descr, index );

    /* Move selection and focused item */
    /* If listbox was empty, set focus to the first item */
    if (descr->nb_items == 1)
         LISTBOX_SetCaretIndex( descr, 0, FALSE );
    /* single select don't change selection index in win31 */
    else if ((ISWIN31) && !(IS_MULTISELECT(descr)))
    {
        descr->selected_item++;
        LISTBOX_SetSelection( descr, descr->selected_item-1, TRUE, FALSE );
    }
    else
    {
        if (index <= descr->selected_item)
        {
            descr->selected_item++;
            descr->focus_item = oldfocus; /* focus not changed */
        }
    }
    return LB_OKAY;
}