#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int uItemState; int /*<<< orphan*/  hdc; } ;
struct TYPE_8__ {TYPE_1__ nmcd; } ;
struct TYPE_7__ {int dwStyle; } ;
typedef  TYPE_2__ TOOLBAR_INFO ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_3__ NMTBCUSTOMDRAW ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BDR_RAISEDINNER ; 
 int /*<<< orphan*/  BDR_SUNKENOUTER ; 
 int BF_MIDDLE ; 
 int BF_RECT ; 
 int BF_SOFT ; 
 int CDIS_CHECKED ; 
 int CDIS_DISABLED ; 
 int CDIS_HOT ; 
 int CDIS_INDETERMINATE ; 
 int CDIS_SELECTED ; 
 int /*<<< orphan*/  DrawEdge (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EDGE_RAISED ; 
 int /*<<< orphan*/  EDGE_SUNKEN ; 
 int TBCDRF_NOEDGES ; 
 int TBSTYLE_FLAT ; 

__attribute__((used)) static void
TOOLBAR_DrawFrame(const TOOLBAR_INFO *infoPtr, const NMTBCUSTOMDRAW *tbcd, const RECT *rect, DWORD dwItemCDFlag)
{
    HDC hdc = tbcd->nmcd.hdc;
    RECT rc = *rect;
    /* if the state is disabled or indeterminate then the button
     * cannot have an interactive look like pressed or hot */
    BOOL non_interactive_state = (tbcd->nmcd.uItemState & CDIS_DISABLED) ||
                                 (tbcd->nmcd.uItemState & CDIS_INDETERMINATE);
    BOOL pressed_look = !non_interactive_state &&
                        ((tbcd->nmcd.uItemState & CDIS_SELECTED) || 
                         (tbcd->nmcd.uItemState & CDIS_CHECKED));

    /* app don't want us to draw any edges */
    if (dwItemCDFlag & TBCDRF_NOEDGES)
        return;

    if (infoPtr->dwStyle & TBSTYLE_FLAT)
    {
        if (pressed_look)
            DrawEdge (hdc, &rc, BDR_SUNKENOUTER, BF_RECT);
        else if ((tbcd->nmcd.uItemState & CDIS_HOT) && !non_interactive_state)
            DrawEdge (hdc, &rc, BDR_RAISEDINNER, BF_RECT);
    }
    else
    {
        if (pressed_look)
            DrawEdge (hdc, &rc, EDGE_SUNKEN, BF_RECT | BF_MIDDLE);
        else
            DrawEdge (hdc, &rc, EDGE_RAISED,
              BF_SOFT | BF_RECT | BF_MIDDLE);
    }
}