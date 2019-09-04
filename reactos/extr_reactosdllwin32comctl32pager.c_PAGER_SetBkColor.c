#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  clrBk; } ;
typedef  TYPE_1__ PAGER_INFO ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int RDW_ERASE ; 
 int RDW_INVALIDATE ; 
 int /*<<< orphan*/  RedrawWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int SWP_FRAMECHANGED ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOMOVE ; 
 int SWP_NOSIZE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static COLORREF
PAGER_SetBkColor (PAGER_INFO* infoPtr, COLORREF clrBk)
{
    COLORREF clrTemp = infoPtr->clrBk;

    infoPtr->clrBk = clrBk;
    TRACE("[%p] %06x\n", infoPtr->hwndSelf, infoPtr->clrBk);

    /* the native control seems to do things this way */
    SetWindowPos(infoPtr->hwndSelf, 0, 0, 0, 0, 0,
		 SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE |
		 SWP_NOZORDER | SWP_NOACTIVATE);

    RedrawWindow(infoPtr->hwndSelf, 0, 0, RDW_ERASE | RDW_INVALIDATE);

    return clrTemp;
}