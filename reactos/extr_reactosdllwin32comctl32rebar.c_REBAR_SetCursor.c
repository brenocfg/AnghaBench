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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int dwStyle; int /*<<< orphan*/  hcurArrow; int /*<<< orphan*/  hcurHorz; int /*<<< orphan*/  hcurVert; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int CCS_VERT ; 
 int /*<<< orphan*/  GetCursorPos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ RBHT_CLIENT ; 
 scalar_t__ RBHT_GRABBER ; 
 int RBS_VERTICALGRIPPER ; 
 int /*<<< orphan*/  REBAR_InternalHitTest (TYPE_1__ const*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScreenToClient (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetCursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
REBAR_SetCursor (const REBAR_INFO *infoPtr, LPARAM lParam)
{
    POINT pt;
    UINT  flags;

    TRACE("code=0x%X  id=0x%X\n", LOWORD(lParam), HIWORD(lParam));

    GetCursorPos (&pt);
    ScreenToClient (infoPtr->hwndSelf, &pt);

    REBAR_InternalHitTest (infoPtr, &pt, &flags, NULL);

    if (flags == RBHT_GRABBER) {
	if ((infoPtr->dwStyle & CCS_VERT) &&
	    !(infoPtr->dwStyle & RBS_VERTICALGRIPPER))
	    SetCursor (infoPtr->hcurVert);
	else
	    SetCursor (infoPtr->hcurHorz);
    }
    else if (flags != RBHT_CLIENT)
	SetCursor (infoPtr->hcurArrow);

    return 0;
}