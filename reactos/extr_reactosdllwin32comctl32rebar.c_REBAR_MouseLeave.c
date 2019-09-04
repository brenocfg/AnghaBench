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
struct TYPE_7__ {int fDraw; int /*<<< orphan*/  rcChevron; } ;
struct TYPE_6__ {int ichevronhotBand; int iOldBand; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  TYPE_2__ REBAR_BAND ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int DRAW_CHEVRONHOT ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* REBAR_GetBand (TYPE_1__*,int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
REBAR_MouseLeave (REBAR_INFO *infoPtr)
{
    if (infoPtr->ichevronhotBand >= 0)
    {
        REBAR_BAND *lpChevronBand = REBAR_GetBand(infoPtr, infoPtr->ichevronhotBand);
        if (lpChevronBand->fDraw & DRAW_CHEVRONHOT)
        {
            lpChevronBand->fDraw &= ~DRAW_CHEVRONHOT;
            InvalidateRect(infoPtr->hwndSelf, &lpChevronBand->rcChevron, TRUE);
        }
    }
    infoPtr->iOldBand = -1;
    infoPtr->ichevronhotBand = -2;

    return TRUE;
}