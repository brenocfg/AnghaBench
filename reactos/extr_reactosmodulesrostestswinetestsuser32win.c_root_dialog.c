#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  DM_GETDEFID ; 
 int DS_CONTROL ; 
 int /*<<< orphan*/  DefDlgProcA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 int GetWindowLongA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WS_CHILD ; 
 int WS_EX_CONTROLPARENT ; 
 int WS_POPUP ; 

__attribute__((used)) static HWND root_dialog(HWND hwnd)
{
    while ((GetWindowLongA(hwnd, GWL_EXSTYLE) & WS_EX_CONTROLPARENT) &&
           (GetWindowLongA(hwnd, GWL_STYLE) & (WS_CHILD|WS_POPUP)) == WS_CHILD)
    {
        HWND parent = GetParent(hwnd);

        /* simple detector for a window being a dialog */
        if (!DefDlgProcA(parent, DM_GETDEFID, 0, 0))
            break;

        hwnd = parent;

        if (!(GetWindowLongA(hwnd, GWL_STYLE) & DS_CONTROL))
            break;
    }

    return hwnd;
}