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
typedef  int UINT ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CloseWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GetActiveWindow () ; 
 int /*<<< orphan*/  GetDesktopWindow () ; 
 int /*<<< orphan*/ * GetFocus () ; 
 int /*<<< orphan*/ * GetForegroundWindow () ; 
 int /*<<< orphan*/  KillTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetActiveWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetForegroundWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTimer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SwitchToThisWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_INTERVAL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  s_bTracing ; 
 int s_nWM_ACTIVATE ; 
 int s_nWM_NCACTIVATE ; 
 int s_nWM_SYSCOMMAND_NOT_SC_RESTORE ; 
 int s_nWM_SYSCOMMAND_SC_RESTORE ; 
 int s_nWM_WINDOWPOSCHANGING ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void
OnTimer(HWND hwnd, UINT id)
{
    KillTimer(hwnd, id);
    switch (id)
    {
        //
        // SwitchToThisWindow(TRUE)
        //
        case 0: // minimize
            SetForegroundWindow(GetDesktopWindow());
            SetActiveWindow(GetDesktopWindow());
            ok(GetForegroundWindow() == NULL, "GetForegroundWindow() != NULL\n");
            ok(GetActiveWindow() == NULL, "GetActiveWindow() != NULL\n");
            ok(GetFocus() == NULL, "GetFocus() != NULL\n");
            CloseWindow(hwnd);  // minimize
            break;
        case 1: // start tracing
            ok(GetForegroundWindow() == NULL, "GetForegroundWindow() != NULL\n");
            ok(GetActiveWindow() == hwnd, "GetActiveWindow() != hwnd\n");
            ok(GetFocus() == NULL, "GetFocus() != NULL\n");
            s_nWM_SYSCOMMAND_SC_RESTORE = 0;
            s_nWM_SYSCOMMAND_NOT_SC_RESTORE = 0;
            s_nWM_NCACTIVATE = 0;
            s_nWM_WINDOWPOSCHANGING = 0;
            s_nWM_ACTIVATE = 0;
            s_bTracing = TRUE;
            SwitchToThisWindow(hwnd, TRUE);
            trace("SwitchToThisWindow(TRUE): tracing...\n");
            break;
        case 2: // tracing done
            s_bTracing = FALSE;
            trace("SwitchToThisWindow(TRUE): tracing done\n");
            ok(GetForegroundWindow() == hwnd, "GetForegroundWindow() != hwnd\n");
            ok(GetActiveWindow() == hwnd, "GetActiveWindow() != hwnd\n");
            ok(GetFocus() == hwnd, "GetFocus() != hwnd\n");
            ok(s_nWM_SYSCOMMAND_SC_RESTORE == 1, "WM_SYSCOMMAND SC_RESTORE: %d\n", s_nWM_SYSCOMMAND_SC_RESTORE);
            ok(!s_nWM_SYSCOMMAND_NOT_SC_RESTORE, "WM_SYSCOMMAND non-SC_RESTORE: %d\n", s_nWM_SYSCOMMAND_NOT_SC_RESTORE);
            ok(s_nWM_NCACTIVATE == 1, "WM_NCACTIVATE: %d\n", s_nWM_NCACTIVATE);
            ok(s_nWM_WINDOWPOSCHANGING == 2, "WM_WINDOWPOSCHANGING: %d\n", s_nWM_WINDOWPOSCHANGING);
            ok(s_nWM_ACTIVATE == 1, "WM_ACTIVATE: %d\n", s_nWM_ACTIVATE);
            break;
        //
        // SwitchToThisWindow(FALSE)
        //
        case 3: // minimize
            SetForegroundWindow(GetDesktopWindow());
            SetActiveWindow(GetDesktopWindow());
            ok(GetForegroundWindow() == NULL, "GetForegroundWindow() != NULL\n");
            ok(GetActiveWindow() == NULL, "GetActiveWindow() != NULL\n");
            ok(GetFocus() == NULL, "GetFocus() != NULL\n");
            CloseWindow(hwnd);  // minimize
            break;
        case 4: // start tracing
            ok(GetForegroundWindow() == NULL, "GetForegroundWindow() != NULL\n");
            ok(GetActiveWindow() == hwnd, "GetActiveWindow() != hwnd\n");
            ok(GetFocus() == NULL, "GetFocus() != NULL\n");
            s_nWM_SYSCOMMAND_SC_RESTORE = 0;
            s_nWM_SYSCOMMAND_NOT_SC_RESTORE = 0;
            s_nWM_NCACTIVATE = 0;
            s_nWM_WINDOWPOSCHANGING = 0;
            s_nWM_ACTIVATE = 0;
            s_bTracing = TRUE;
            SwitchToThisWindow(hwnd, FALSE);
            trace("SwitchToThisWindow(FALSE): tracing...\n");
            break;
        case 5: // tracing done
            s_bTracing = FALSE;
            trace("SwitchToThisWindow(FALSE): tracing done\n");
            ok(GetForegroundWindow() == NULL, "GetForegroundWindow() != NULL\n");
            ok(GetActiveWindow() == hwnd, "GetActiveWindow() != hwnd\n");
            ok(GetFocus() == NULL, "GetFocus() != NULL\n");
            ok(!s_nWM_SYSCOMMAND_SC_RESTORE, "WM_SYSCOMMAND SC_RESTORE: %d\n", s_nWM_SYSCOMMAND_SC_RESTORE);
            ok(!s_nWM_SYSCOMMAND_NOT_SC_RESTORE, "WM_SYSCOMMAND non-SC_RESTORE: %d\n", s_nWM_SYSCOMMAND_NOT_SC_RESTORE);
            ok(!s_nWM_NCACTIVATE, "WM_NCACTIVATE: %d\n", s_nWM_NCACTIVATE);
            ok(!s_nWM_WINDOWPOSCHANGING, "WM_WINDOWPOSCHANGING: %d\n", s_nWM_WINDOWPOSCHANGING);
            ok(!s_nWM_ACTIVATE, "WM_ACTIVATE: %d\n", s_nWM_ACTIVATE);
            break;
        default: // finish
            DestroyWindow(hwnd);
            return;
    }
    SetTimer(hwnd, id + 1, TIMER_INTERVAL, NULL);
}