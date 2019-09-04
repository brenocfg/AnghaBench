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
struct TYPE_5__ {int fStatus; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  uNumBands; scalar_t__ DoRedraw; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  int LRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BAND_NEEDS_REDRAW ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REBAR_ForceResize (TYPE_1__*) ; 
 int /*<<< orphan*/  REBAR_MoveChildWindows (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,char*,int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline LRESULT
REBAR_SetRedraw (REBAR_INFO *infoPtr, BOOL redraw)
{
    BOOL oldredraw = infoPtr->DoRedraw;

    TRACE("set to %s, fStatus=%08x\n",
	  (redraw) ? "TRUE" : "FALSE", infoPtr->fStatus);
    infoPtr->DoRedraw = redraw;
    if (redraw) {
	if (infoPtr->fStatus & BAND_NEEDS_REDRAW) {
	    REBAR_MoveChildWindows (infoPtr, 0, infoPtr->uNumBands);
	    REBAR_ForceResize (infoPtr);
	    InvalidateRect (infoPtr->hwndSelf, NULL, TRUE);
	}
	infoPtr->fStatus &= ~BAND_NEEDS_REDRAW;
    }
    return (oldredraw) ? -1 : 0;
}