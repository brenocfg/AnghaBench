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
struct TYPE_5__ {int nMaxTipWidth; int nTool; int nCurrentTool; int nTrackTool; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  bTrackActive; int /*<<< orphan*/  bActive; } ;
typedef  TYPE_1__ TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 TYPE_1__* Alloc (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HWND_TOP ; 
 int SWP_HIDEWINDOW ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TOOLTIPS_InitSystemSettings (TYPE_1__*) ; 
 int /*<<< orphan*/  TOOLTIPS_SetDelayTime (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TTDT_AUTOMATIC ; 

__attribute__((used)) static LRESULT
TOOLTIPS_Create (HWND hwnd)
{
    TOOLTIPS_INFO *infoPtr;

    /* allocate memory for info structure */
    infoPtr = Alloc (sizeof(TOOLTIPS_INFO));
    SetWindowLongPtrW (hwnd, 0, (DWORD_PTR)infoPtr);

    /* initialize info structure */
    infoPtr->bActive = TRUE;
    infoPtr->bTrackActive = FALSE;

    infoPtr->nMaxTipWidth = -1;
    infoPtr->nTool = -1;
    infoPtr->nCurrentTool = -1;
    infoPtr->nTrackTool = -1;
    infoPtr->hwndSelf = hwnd;

    /* initialize colours and fonts */
    TOOLTIPS_InitSystemSettings(infoPtr);

    TOOLTIPS_SetDelayTime(infoPtr, TTDT_AUTOMATIC, 0);

    SetWindowPos (hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_HIDEWINDOW | SWP_NOACTIVATE);

    return 0;
}