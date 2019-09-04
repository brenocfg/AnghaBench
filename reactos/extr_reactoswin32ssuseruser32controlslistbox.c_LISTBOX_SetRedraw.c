#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int style; scalar_t__ top_item; scalar_t__ page_size; scalar_t__ nb_items; int /*<<< orphan*/  self; } ;
typedef  TYPE_1__ LB_DESCR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int LBS_DISPLAYCHANGED ; 
 int LBS_NOREDRAW ; 
 int /*<<< orphan*/  LISTBOX_UpdateScroll (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void LISTBOX_SetRedraw( LB_DESCR *descr, BOOL on )
{
    if (on)
    {
        if (!(descr->style & LBS_NOREDRAW)) return;
        descr->style &= ~LBS_NOREDRAW;
        if (descr->style & LBS_DISPLAYCHANGED)
        {     /* page was changed while setredraw false, refresh automatically */
            InvalidateRect(descr->self, NULL, TRUE);
            if ((descr->top_item + descr->page_size) > descr->nb_items)
            {      /* reset top of page if less than number of items/page */
                descr->top_item = descr->nb_items - descr->page_size;
                if (descr->top_item < 0) descr->top_item = 0;
            }
            descr->style &= ~LBS_DISPLAYCHANGED;
        }
        LISTBOX_UpdateScroll( descr );
    }
    else descr->style |= LBS_NOREDRAW;
}