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
struct TYPE_5__ {scalar_t__ horz_extent; scalar_t__ width; scalar_t__ horz_pos; int /*<<< orphan*/  self; int /*<<< orphan*/  focus_item; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ LB_DESCR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int LISTBOX_GetItemRect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LISTBOX_UpdateScroll (TYPE_1__*) ; 
 int SW_ERASE ; 
 int SW_INVALIDATE ; 
 int SW_SCROLLCHILDREN ; 
 int /*<<< orphan*/  ScrollWindowEx (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ abs (scalar_t__) ; 

__attribute__((used)) static void LISTBOX_SetHorizontalPos( LB_DESCR *descr, INT pos )
{
    INT diff;

    if (pos > descr->horz_extent - descr->width)
        pos = descr->horz_extent - descr->width;
    if (pos < 0) pos = 0;
    if (!(diff = descr->horz_pos - pos)) return;
    TRACE("[%p]: new horz pos = %d\n", descr->self, pos );
    descr->horz_pos = pos;
    LISTBOX_UpdateScroll( descr );
    if (abs(diff) < descr->width)
    {
        RECT rect;
        /* Invalidate the focused item so it will be repainted correctly */
        if (LISTBOX_GetItemRect( descr, descr->focus_item, &rect ) == 1)
            InvalidateRect( descr->self, &rect, TRUE );
        ScrollWindowEx( descr->self, diff, 0, NULL, NULL, 0, NULL,
                          SW_INVALIDATE | SW_ERASE | SW_SCROLLCHILDREN );
    }
    else
        InvalidateRect( descr->self, NULL, TRUE );
}