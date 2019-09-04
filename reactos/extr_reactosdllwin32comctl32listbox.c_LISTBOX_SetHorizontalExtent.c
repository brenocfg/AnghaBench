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
typedef  int /*<<< orphan*/  info ;
struct TYPE_7__ {int style; scalar_t__ horz_extent; scalar_t__ horz_pos; scalar_t__ width; int /*<<< orphan*/  self; } ;
struct TYPE_6__ {int cbSize; scalar_t__ nMax; int /*<<< orphan*/  fMask; scalar_t__ nMin; } ;
typedef  TYPE_1__ SCROLLINFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__ LB_DESCR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int LBS_DISABLENOSCROLL ; 
 int LBS_MULTICOLUMN ; 
 int /*<<< orphan*/  LB_OKAY ; 
 int /*<<< orphan*/  LISTBOX_SetHorizontalPos (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  SB_HORZ ; 
 int /*<<< orphan*/  SIF_DISABLENOSCROLL ; 
 int /*<<< orphan*/  SIF_RANGE ; 
 int /*<<< orphan*/  SetScrollInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int WS_HSCROLL ; 

__attribute__((used)) static LRESULT LISTBOX_SetHorizontalExtent( LB_DESCR *descr, INT extent )
{
    if (descr->style & LBS_MULTICOLUMN)
        return LB_OKAY;
    if (extent == descr->horz_extent) return LB_OKAY;
    TRACE("[%p]: new horz extent = %d\n", descr->self, extent );
    descr->horz_extent = extent;
    if (descr->style & WS_HSCROLL) {
        SCROLLINFO info;
        info.cbSize = sizeof(info);
        info.nMin  = 0;
        info.nMax = descr->horz_extent ? descr->horz_extent - 1 : 0;
        info.fMask = SIF_RANGE;
        if (descr->style & LBS_DISABLENOSCROLL)
            info.fMask |= SIF_DISABLENOSCROLL;
        SetScrollInfo( descr->self, SB_HORZ, &info, TRUE );
    }
    if (descr->horz_pos > extent - descr->width)
        LISTBOX_SetHorizontalPos( descr, extent - descr->width );
    return LB_OKAY;
}