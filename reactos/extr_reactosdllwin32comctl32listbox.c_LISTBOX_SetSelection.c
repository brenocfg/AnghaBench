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
struct TYPE_10__ {int selected_item; int style; int nb_items; TYPE_2__* lphc; TYPE_1__* items; } ;
struct TYPE_9__ {int /*<<< orphan*/  wState; } ;
struct TYPE_8__ {int /*<<< orphan*/  selected; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_3__ LB_DESCR ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CBF_SELCHANGE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LBN_SELCANCEL ; 
 int /*<<< orphan*/  LBN_SELCHANGE ; 
 int LBS_MULTIPLESEL ; 
 int LBS_NOSEL ; 
 int /*<<< orphan*/  LB_ERR ; 
 int /*<<< orphan*/  LB_OKAY ; 
 int /*<<< orphan*/  LISTBOX_RepaintItem (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LISTBOX_SelectItemRange (TYPE_3__*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  ODA_SELECT ; 
 int /*<<< orphan*/  SEND_NOTIFICATION (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int,int,char*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT LISTBOX_SetSelection( LB_DESCR *descr, INT index,
                                     BOOL on, BOOL send_notify )
{
    TRACE( "cur_sel=%d index=%d notify=%s\n",
           descr->selected_item, index, send_notify ? "YES" : "NO" );

    if (descr->style & LBS_NOSEL)
    {
        descr->selected_item = index;
        return LB_ERR;
    }
    if ((index < -1) || (index >= descr->nb_items)) return LB_ERR;
    if (descr->style & LBS_MULTIPLESEL)
    {
        if (index == -1)  /* Select all items */
            return LISTBOX_SelectItemRange( descr, 0, descr->nb_items, on );
        else  /* Only one item */
            return LISTBOX_SelectItemRange( descr, index, index, on );
    }
    else
    {
        INT oldsel = descr->selected_item;
        if (index == oldsel) return LB_OKAY;
        if (oldsel != -1) descr->items[oldsel].selected = FALSE;
        if (index != -1) descr->items[index].selected = TRUE;
        if (oldsel != -1) LISTBOX_RepaintItem( descr, oldsel, ODA_SELECT );
        descr->selected_item = index;
        if (index != -1) LISTBOX_RepaintItem( descr, index, ODA_SELECT );
        if (send_notify && descr->nb_items) SEND_NOTIFICATION( descr,
                               (index != -1) ? LBN_SELCHANGE : LBN_SELCANCEL );
	else
	    if( descr->lphc ) /* set selection change flag for parent combo */
		descr->lphc->wState |= CBF_SELCHANGE;
    }
    return LB_OKAY;
}