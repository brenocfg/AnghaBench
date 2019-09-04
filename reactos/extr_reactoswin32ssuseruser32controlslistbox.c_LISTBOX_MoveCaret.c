#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ nb_items; int style; int anchor_item; scalar_t__ focus_item; } ;
typedef  TYPE_1__ LB_DESCR ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int LBS_EXTENDEDSEL ; 
 int LBS_MULTIPLESEL ; 
 int /*<<< orphan*/  LISTBOX_DrawFocusRect (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LISTBOX_MakeItemVisible (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LISTBOX_SelectItemRange (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LISTBOX_SetSelection (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ max (scalar_t__,int) ; 
 scalar_t__ min (scalar_t__,int) ; 

__attribute__((used)) static void LISTBOX_MoveCaret( LB_DESCR *descr, INT index, BOOL fully_visible )
{
    TRACE("old focus %d, index %d\n", descr->focus_item, index);

    if ((index <  0) || (index >= descr->nb_items))
        return;

    /* Important, repaint needs to be done in this order if
       you want to mimic Windows behavior:
       1. Remove the focus and paint the item
       2. Remove the selection and paint the item(s)
       3. Set the selection and repaint the item(s)
       4. Set the focus to 'index' and repaint the item */

    /* 1. remove the focus and repaint the item */
    LISTBOX_DrawFocusRect( descr, FALSE );

    /* 2. then turn off the previous selection */
    /* 3. repaint the new selected item */
    if (descr->style & LBS_EXTENDEDSEL)
    {
        if (descr->anchor_item != -1)
        {
            INT first = min( index, descr->anchor_item );
            INT last  = max( index, descr->anchor_item );
            if (first > 0)
                LISTBOX_SelectItemRange( descr, 0, first - 1, FALSE );
            LISTBOX_SelectItemRange( descr, last + 1, -1, FALSE );
            LISTBOX_SelectItemRange( descr, first, last, TRUE );
        }
    }
    else if (!(descr->style & LBS_MULTIPLESEL))
    {
        /* Set selection to new caret item */
        LISTBOX_SetSelection( descr, index, TRUE, FALSE );
    }

    /* 4. repaint the new item with the focus */
    descr->focus_item = index;
    LISTBOX_MakeItemVisible( descr, index, fully_visible );
    LISTBOX_DrawFocusRect( descr, TRUE );
}