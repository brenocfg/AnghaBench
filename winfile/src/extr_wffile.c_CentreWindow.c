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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int right; int left; int bottom; int top; } ;
typedef  TYPE_1__ RECT ;
typedef  int LONG ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/ * GetDesktopWindow () ; 
 int /*<<< orphan*/ * GetParent (int /*<<< orphan*/ *) ; 
 int GetWindowLongPtr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int SWP_NOSIZE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SetForegroundWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int WS_CHILD ; 

VOID CentreWindow(
    HWND hwnd)
{
    RECT    rect;
    RECT    rectParent;
    HWND    hwndParent;
    LONG    dx, dy;
    LONG    dxParent, dyParent;
    LONG    Style;

    //
    //  Get window rect.
    //
    GetWindowRect(hwnd, &rect);

    dx = rect.right - rect.left;
    dy = rect.bottom - rect.top;

    //
    //  Get parent rect.
    //
    Style = GetWindowLongPtr(hwnd, GWL_STYLE);
    if ((Style & WS_CHILD) == 0)
    {
        hwndParent = GetDesktopWindow();
    }
    else
    {
        hwndParent = GetParent(hwnd);
        if (hwndParent == NULL)
        {
            hwndParent = GetDesktopWindow();
        }
    }
    GetWindowRect(hwndParent, &rectParent);

    dxParent = rectParent.right - rectParent.left;
    dyParent = rectParent.bottom - rectParent.top;

    //
    //  Centre the child in the parent.
    //
    rect.left = (dxParent - dx) / 2;
    rect.top  = (dyParent - dy) / 3;

    //
    //  Move the child into position.
    //
    SetWindowPos( hwnd,
                  NULL,
                  rect.left,
                  rect.top,
                  0,
                  0,
                  SWP_NOSIZE | SWP_NOZORDER );

    SetForegroundWindow(hwnd);
}