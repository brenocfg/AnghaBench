#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_11__ {scalar_t__ top; scalar_t__ bottom; } ;
struct TYPE_10__ {int /*<<< orphan*/  Self; scalar_t__ minHeight; scalar_t__ verticalBorder; scalar_t__ hDefaultFont; scalar_t__ hFont; } ;
struct TYPE_9__ {int tmInternalLeading; scalar_t__ tmHeight; } ;
typedef  TYPE_1__ TEXTMETRICW ;
typedef  TYPE_2__ STATUS_INFO ;
typedef  TYPE_3__ RECT ;
typedef  int /*<<< orphan*/  HTHEME ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  COMCTL32_GetFontMetrics (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetThemeBackgroundExtent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  GetWindowTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CYBORDER ; 
 int /*<<< orphan*/  SP_PANE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int,scalar_t__) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 

__attribute__((used)) static UINT
STATUSBAR_ComputeHeight(STATUS_INFO *infoPtr)
{
    HTHEME theme;
    UINT height;
    TEXTMETRICW tm;
    int margin;

    COMCTL32_GetFontMetrics(infoPtr->hFont ? infoPtr->hFont : infoPtr->hDefaultFont, &tm);
    margin = (tm.tmInternalLeading ? tm.tmInternalLeading : 2);
    height = max(tm.tmHeight + margin + 2*GetSystemMetrics(SM_CYBORDER), infoPtr->minHeight) + infoPtr->verticalBorder;

    if ((theme = GetWindowTheme(infoPtr->Self)))
    {
        /* Determine bar height from theme such that the content area is
         * textHeight pixels large */
        HDC hdc = GetDC(infoPtr->Self);
        RECT r;

        SetRect(&r, 0, 0, 0, max(infoPtr->minHeight, tm.tmHeight));
        if (SUCCEEDED(GetThemeBackgroundExtent(theme, hdc, SP_PANE, 0, &r, &r)))
        {
            height = r.bottom - r.top;
        }
        ReleaseDC(infoPtr->Self, hdc);
    }

    TRACE("    textHeight=%d+%d, final height=%d\n", tm.tmHeight, tm.tmInternalLeading, height);
    return height;
}