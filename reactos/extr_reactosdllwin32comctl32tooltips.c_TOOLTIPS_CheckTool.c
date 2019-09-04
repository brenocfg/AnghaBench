#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* tools; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_5__ {int uFlags; scalar_t__ hwnd; scalar_t__ uId; } ;
typedef  TYPE_1__ TTTOOL_INFO ;
typedef  TYPE_2__ TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetActiveWindow () ; 
 int /*<<< orphan*/  GetCursorPos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetParent (scalar_t__) ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScreenToClient (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TOOLTIPS_GetToolFromPoint (TYPE_2__ const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TOOLTIPS_IsWindowActive (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int TTF_IDISHWND ; 
 int /*<<< orphan*/  TTM_WINDOWFROMPOINT ; 
 int TTS_ALWAYSTIP ; 

__attribute__((used)) static INT
TOOLTIPS_CheckTool (const TOOLTIPS_INFO *infoPtr, BOOL bShowTest)
{
    POINT pt;
    HWND hwndTool;
    INT nTool;

    GetCursorPos (&pt);
    hwndTool = (HWND)SendMessageW (infoPtr->hwndSelf, TTM_WINDOWFROMPOINT, 0, (LPARAM)&pt);
    if (hwndTool == 0)
	return -1;

    ScreenToClient (hwndTool, &pt);
    nTool = TOOLTIPS_GetToolFromPoint (infoPtr, hwndTool, &pt);
    if (nTool == -1)
	return -1;

    if (!(GetWindowLongW (infoPtr->hwndSelf, GWL_STYLE) & TTS_ALWAYSTIP) && bShowTest)
    {
        TTTOOL_INFO *ti = &infoPtr->tools[nTool];
        HWND hwnd = (ti->uFlags & TTF_IDISHWND) ? (HWND)ti->uId : ti->hwnd;

        if (!TOOLTIPS_IsWindowActive(hwnd))
        {
            TRACE("not active: hwnd %p, parent %p, active %p\n",
                  hwnd, GetParent(hwnd), GetActiveWindow());
            return -1;
        }
    }

    TRACE("tool %d\n", nTool);

    return nTool;
}