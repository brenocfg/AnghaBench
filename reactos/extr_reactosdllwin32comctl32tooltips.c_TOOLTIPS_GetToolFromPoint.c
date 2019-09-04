#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_5__ {size_t uNumTools; TYPE_1__* tools; } ;
struct TYPE_4__ {int uFlags; scalar_t__ hwnd; scalar_t__ uId; int /*<<< orphan*/  rect; } ;
typedef  TYPE_1__ TTTOOL_INFO ;
typedef  TYPE_2__ TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  POINT ;
typedef  size_t INT ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int /*<<< orphan*/  PtInRect (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int TTF_IDISHWND ; 

__attribute__((used)) static INT
TOOLTIPS_GetToolFromPoint (const TOOLTIPS_INFO *infoPtr, HWND hwnd, const POINT *lpPt)
{
    TTTOOL_INFO *toolPtr;
    UINT nTool;

    for (nTool = 0; nTool < infoPtr->uNumTools; nTool++) {
	toolPtr = &infoPtr->tools[nTool];

	if (!(toolPtr->uFlags & TTF_IDISHWND)) {
	    if (hwnd != toolPtr->hwnd)
		continue;
	    if (!PtInRect (&toolPtr->rect, *lpPt))
		continue;
	    return nTool;
	}
    }

    for (nTool = 0; nTool < infoPtr->uNumTools; nTool++) {
	toolPtr = &infoPtr->tools[nTool];

	if (toolPtr->uFlags & TTF_IDISHWND) {
	    if ((HWND)toolPtr->uId == hwnd)
		return nTool;
	}
    }

    return -1;
}