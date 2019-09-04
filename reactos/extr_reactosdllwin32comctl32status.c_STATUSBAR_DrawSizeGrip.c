#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* bottom; void* top; void* right; void* left; } ;
struct TYPE_10__ {void* cy; void* cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_2__* LPRECT ;
typedef  scalar_t__ HTHEME ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  DFCS_SCROLLSIZEGRIP ; 
 int /*<<< orphan*/  DFC_SCROLL ; 
 int /*<<< orphan*/  DrawFrameControl (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawThemeBackground (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 void* GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetThemePartSize (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SM_CXVSCROLL ; 
 int /*<<< orphan*/  SM_CYHSCROLL ; 
 int /*<<< orphan*/  SP_GRIPPER ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_DRAW ; 
 void* max (void*,void*) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_2__*) ; 

__attribute__((used)) static void
STATUSBAR_DrawSizeGrip (HTHEME theme, HDC hdc, LPRECT lpRect)
{
    RECT rc = *lpRect;

    TRACE("draw size grip %s\n", wine_dbgstr_rect(lpRect));

    if (theme)
    {
        SIZE gripperSize;
        if (SUCCEEDED (GetThemePartSize (theme, hdc, SP_GRIPPER, 0, lpRect, 
            TS_DRAW, &gripperSize)))
        {
            rc.left = rc.right - gripperSize.cx;
            rc.top = rc.bottom - gripperSize.cy;
            if (SUCCEEDED (DrawThemeBackground(theme, hdc, SP_GRIPPER, 0, &rc, NULL)))
                return;
        }
    }

    rc.left = max( rc.left, rc.right - GetSystemMetrics(SM_CXVSCROLL) - 1 );
    rc.top  = max( rc.top, rc.bottom - GetSystemMetrics(SM_CYHSCROLL) - 1 );
    DrawFrameControl( hdc, &rc, DFC_SCROLL, DFCS_SCROLLSIZEGRIP );
}