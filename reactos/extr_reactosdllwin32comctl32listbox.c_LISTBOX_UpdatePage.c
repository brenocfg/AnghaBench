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
struct TYPE_4__ {int item_height; int height; int page_size; int style; int /*<<< orphan*/  top_item; int /*<<< orphan*/  self; } ;
typedef  TYPE_1__ LB_DESCR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int LBS_MULTICOLUMN ; 
 int /*<<< orphan*/  LISTBOX_SetTopItem (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void LISTBOX_UpdatePage( LB_DESCR *descr )
{
    INT page_size;

    if ((descr->item_height == 0) || (page_size = descr->height / descr->item_height) < 1)
                       page_size = 1;
    if (page_size == descr->page_size) return;
    descr->page_size = page_size;
    if (descr->style & LBS_MULTICOLUMN)
        InvalidateRect( descr->self, NULL, TRUE );
    LISTBOX_SetTopItem( descr, descr->top_item, FALSE );
}